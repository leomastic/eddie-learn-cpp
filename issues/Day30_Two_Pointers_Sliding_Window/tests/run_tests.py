#!/usr/bin/env python3

import argparse
import random
import subprocess
import tempfile
import time
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
BASE_SEED = 30030
MAX_N = 200_000


def input_for(problem, values, *parameters):
    if problem == 3:
        team_a, team_b = values
        return (
            f"{len(team_a)} {len(team_b)}\n"
            f"{' '.join(map(str, team_a))}\n"
            f"{' '.join(map(str, team_b))}\n"
        )
    return (
        f"{len(values)} {' '.join(map(str, parameters))}\n"
        f"{' '.join(map(str, values))}\n"
    )


def brute1(values, budget):
    best = 0
    for left in range(len(values)):
        total = 0
        for right in range(left, len(values)):
            total += values[right]
            if total <= budget:
                best = max(best, right - left + 1)
    return best


def brute2(values, limit):
    best = 0
    for left in range(len(values)):
        categories = set()
        for right in range(left, len(values)):
            categories.add(values[right])
            if len(categories) <= limit:
                best = max(best, right - left + 1)
    return best


def brute3(team_a, team_b):
    return min(abs(a - b) for a in team_a for b in team_b)


def brute4(values, target):
    best = len(values) + 1
    for left in range(len(values)):
        total = 0
        for right in range(left, len(values)):
            total += values[right]
            if total >= target:
                best = min(best, right - left + 1)
    return 0 if best == len(values) + 1 else best


def brute5(values, limit):
    count = 0
    for left in range(len(values)):
        low = high = values[left]
        for right in range(left, len(values)):
            low = min(low, values[right])
            high = max(high, values[right])
            if high - low <= limit:
                count += 1
    return count


BRUTE = {1: brute1, 2: brute2, 3: brute3, 4: brute4, 5: brute5}


def compiled_solutions(build_dir):
    version = subprocess.run(
        ["g++", "--version"],
        check=True,
        capture_output=True,
        text=True,
    ).stdout.splitlines()[0]
    print(f"Compiler: {version}")
    executables = {}
    for problem in range(1, 6):
        source = ROOT / f"problem{problem}.cpp"
        executable = build_dir / f"problem{problem}"
        subprocess.run(
            [
                "g++",
                "-std=c++17",
                "-O2",
                "-Wall",
                "-Wextra",
                "-Wpedantic",
                str(source),
                "-o",
                str(executable),
            ],
            check=True,
        )
        executables[problem] = executable
    return executables


def run_program(executable, data, memory_file=None):
    command = [str(executable)]
    if memory_file is not None:
        command = ["/usr/bin/time", "-f", "%M", "-o", str(memory_file)] + command
    started = time.perf_counter()
    result = subprocess.run(
        command,
        input=data,
        capture_output=True,
        text=True,
        timeout=60,
        check=True,
    )
    elapsed = time.perf_counter() - started
    output = result.stdout.strip()
    return output, elapsed


def check_case(executable, data, expected):
    output, _ = run_program(executable, data)
    actual = output.splitlines()
    if actual != [str(expected)]:
        raise AssertionError(
            f"{executable.name}: expected {expected}, received {output!r}\n"
            f"Input:\n{data[:1000]}"
        )


def fixed_cases():
    cases = {
        1: [
            ([3, 1, 4, 2, 5, 1], (8,), 3),
            ([1], (0,), 0),
            ([1], (1,), 1),
            ([1, 1, 1], (0,), 0),
            ([5, 1, 1], (4,), 2),
            ([2, 3, 4], (9,), 3),
            ([1_000_000_000] * 3, (10**14,), 3),
        ],
        2: [
            ([1, 2, 1, 3, 3, 2, 2, 4], (2,), 4),
            ([7, 7, 7], (0,), 0),
            ([7, 7, 7], (1,), 3),
            ([1, 2, 3, 4], (4,), 4),
            ([1, 2, 1, 3, 2, 1], (2,), 3),
            ([1, 1_000_000, 1_000_000], (2,), 3),
        ],
        3: [
            (([20, 3, 14, 8], [30, 11, 6]), (), 2),
            (([9], [9]), (), 0),
            (([1], [1_000_000_000]), (), 999_999_999),
            (([2, 2, 20], [3, 2, 2]), (), 0),
        ],
        4: [
            ([2, 3, 1, 2, 4, 3], (7,), 2),
            ([1, 1, 1], (4,), 0),
            ([8], (8,), 1),
            ([2, 3, 4], (9,), 3),
            ([1, 2, 3], (1,), 1),
            ([1_000_000_000] * 3, (2_000_000_000,), 2),
        ],
        5: [
            ([1, 3, 2, 5], (2,), 7),
            ([4, 4, 4, 4], (0,), 10),
            ([1, 2, 3, 4, 5], (4,), 15),
            ([1, 1_000_000_000, 1, 1_000_000_000], (0,), 4),
            ([1, 1_000_000_000, 1, 1_000_000_000], (999_999_999,), 10),
        ],
    }
    return cases


def random_case(problem, rng):
    if problem == 1:
        values = [rng.randint(1, 12) for _ in range(rng.randint(1, 12))]
        parameters = (rng.randint(0, 40),)
        expected = brute1(values, *parameters)
    elif problem == 2:
        values = [rng.randint(1, 7) for _ in range(rng.randint(1, 15))]
        parameters = (rng.randint(0, len(values)),)
        expected = brute2(values, *parameters)
    elif problem == 3:
        values = (
            [rng.randint(1, 30) for _ in range(rng.randint(1, 10))],
            [rng.randint(1, 30) for _ in range(rng.randint(1, 10))],
        )
        parameters = ()
        expected = brute3(*values)
    elif problem == 4:
        values = [rng.randint(1, 12) for _ in range(rng.randint(1, 12))]
        parameters = (rng.randint(1, 60),)
        expected = brute4(values, *parameters)
    else:
        values = [rng.randint(1, 20) for _ in range(rng.randint(1, 14))]
        parameters = (rng.randint(0, 20),)
        expected = brute5(values, *parameters)
    return values, parameters, expected


def stress_case(problem):
    if problem == 1:
        values = [1] * MAX_N
        parameters = (10**14,)
        expected = MAX_N
    elif problem == 2:
        values = [index % 1000 + 1 for index in range(MAX_N)]
        parameters = (1000,)
        expected = MAX_N
    elif problem == 3:
        values = (
            list(range(2, 2 * MAX_N + 1, 2)),
            list(range(1, 2 * MAX_N, 2)),
        )
        parameters = ()
        expected = 1
    elif problem == 4:
        values = [1] * MAX_N
        parameters = (MAX_N,)
        expected = MAX_N
    else:
        values = [1 if index % 2 == 0 else 1_000_000_000 for index in range(MAX_N)]
        parameters = (999_999_999,)
        expected = MAX_N * (MAX_N + 1) // 2
    return values, parameters, expected


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--skip-stress",
        action="store_true",
        help="skip the maximum-size performance and memory cases",
    )
    args = parser.parse_args()

    time_path = Path("/usr/bin/time")
    time_available = (
        time_path.is_file()
        and subprocess.run(
            [str(time_path), "--version"],
            capture_output=True,
            text=True,
        ).stdout.startswith("time (GNU Time)")
    )
    with tempfile.TemporaryDirectory(prefix="day30-tests-") as temporary:
        build_dir = Path(temporary)
        executables = compiled_solutions(build_dir)

        fixed_count = 0
        for problem, examples in fixed_cases().items():
            for values, parameters, expected in examples:
                check_case(
                    executables[problem],
                    input_for(problem, values, *parameters),
                    expected,
                )
                fixed_count += 1
        print(f"Samples and boundary cases: {fixed_count} passed")

        for problem in range(1, 6):
            rng = random.Random(BASE_SEED + problem)
            for _ in range(100):
                values, parameters, expected = random_case(problem, rng)
                check_case(
                    executables[problem],
                    input_for(problem, values, *parameters),
                    expected,
                )
            print(
                f"Problem {problem}: 100 brute-force comparisons passed "
                f"(seed {BASE_SEED + problem})"
            )

        if args.skip_stress:
            print("Stress tests: skipped")
            return

        if time_available:
            print("Peak RSS uses GNU /usr/bin/time; units are KiB.")
        else:
            print("Peak RSS unavailable; /usr/bin/time was not found.")

        for problem in range(1, 6):
            values, parameters, expected = stress_case(problem)
            data = input_for(problem, values, *parameters)
            memory_file = build_dir / f"problem{problem}.rss"
            measure_memory = time_available
            output, elapsed = run_program(
                executables[problem],
                data,
                memory_file if measure_memory else None,
            )
            if output.splitlines() != [str(expected)]:
                raise AssertionError(
                    f"Problem {problem} stress test: expected {expected}, "
                    f"received {output!r}"
                )
            memory = (
                f", peak RSS {memory_file.read_text().strip()} KiB"
                if measure_memory
                else ""
            )
            print(
                f"Problem {problem}: N={MAX_N}"
                f"{', M=200000' if problem == 3 else ''}, "
                f"output {expected}, {elapsed:.3f}s{memory}"
            )

        print("All Day30 checks passed.")


if __name__ == "__main__":
    main()
