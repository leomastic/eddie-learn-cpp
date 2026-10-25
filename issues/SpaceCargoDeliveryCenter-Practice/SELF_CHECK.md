# 65. SELF_CHECK.md

## Question 1
What is composition?

Composition is a design approach where one class contains another class as a part of its internal state. In this project, a Vehicle owns a FuelTank object, so the vehicle is built from smaller related objects rather than relying on unrelated data.

## Question 2
Where is composition used in this project?

Composition is used in Vehicle, which contains a FuelTank object. It is also reflected in the overall design because DeliveryCenter coordinates multiple Cargo and Vehicle objects, but the clearest example is the Vehicle containing FuelTank.

## Question 3
Why does Vehicle contain a FuelTank instead of storing only an integer?

Because fuel is not just a number; it has behavior and rules. A FuelTank object can enforce valid fuel values, track its own state, and provide methods like consume(), refuel(), and status checks. That makes the design cleaner and less error-prone than storing a plain integer.

## Question 4
Which class owns the rule that fuel must remain between 0 and 100?

The FuelTank class owns that rule. It clamps the fuel level when created or changed and keeps the value inside the valid range.

## Question 5
Why should Vehicle call fuelTank_.consume() instead of changing fuel directly?

Because the fuel logic should stay inside FuelTank. Calling consume() keeps the fuel state consistent with the tank’s own rules, such as preventing negative values and keeping the value within range.

## Question 6
Which class owns cargo-status transitions?

The Cargo class owns cargo-status transitions. It is responsible for changing a cargo package from Waiting to Loaded, InTransit, Delivered, or Cancelled.

## Question 7
Which class owns vehicle-status transitions?

The Vehicle class owns vehicle-status transitions. It decides when a vehicle becomes Loaded, InTransit, Refueling, OutOfService, or Available.

## Question 8
Why is Vehicle::updateStatus() private?

Because status updates are an internal detail of the Vehicle class. It should only be called from methods that change the vehicle’s state, so keeping it private prevents outside code from accidentally putting the object into an invalid state.

## Question 9
Why does Cargo store the assigned vehicle ID instead of a copy of the complete Vehicle?

Because Cargo only needs to know which vehicle is linked to it. Storing the vehicle ID is lighter, simpler, and avoids unnecessary copying of the full object. It also keeps the relationship easy to inspect and update.

## Question 10
Why does Vehicle store the assigned cargo ID instead of a copy of the complete Cargo?

For the same reason as Cargo. A Vehicle only needs to know which cargo is assigned to it, and storing an ID is enough. It avoids coupling the vehicle to the full cargo object and keeps the data model simple.

## Question 11
Which class coordinates Cargo and Vehicle objects?

The DeliveryCenter class coordinates them. It manages the relationship between cargo packages and vehicles, including loading, delivery, cancellation, and summary operations.

## Question 12
Why must cargo loading update both objects?

Because the two objects must stay consistent with each other. If the cargo is marked as loaded but the vehicle does not hold that cargo assignment, the system would have a broken state.

## Question 13
What inconsistent state would exist if Cargo became Loaded but Vehicle remained Available?

The system would show that cargo is loaded but the vehicle is still available and has no assigned cargo. That would be contradictory and would make the program behave unpredictably.

## Question 14
Why does loading rollback the cargo assignment if vehicle loading fails?

Because the operation must be atomic. If the vehicle cannot accept the cargo, the cargo should not remain assigned to that vehicle, otherwise the objects would be left in a partially updated state.

## Question 15
Why are index lookup functions used?

Index lookup functions make it easier to find an object by its unique ID. They also avoid repeating manual loops and provide a simple way to check whether an object exists.

## Question 16
What does return value -1 mean?

It means the searched object was not found.

## Question 17
Why must an index be validated before accessing a vector?

Because an invalid index can cause undefined behavior or a crash. Checking the index first ensures the code only accesses a real element.

## Question 18
Why must vehicle IDs and cargo IDs be unique?

Because IDs are used as identifiers for lookup and relationship tracking. If two objects shared the same ID, the system could not reliably tell them apart or prevent duplicates.

## Question 19
Why can a loaded vehicle not begin refueling?

Because a loaded vehicle is carrying cargo and is expected to be in a valid operational state for transport. Refueling should not be allowed while the vehicle is busy with a loaded assignment.

## Question 20
Why can an empty out-of-service vehicle begin refueling?

Because it is already out of service and has no fuel. Refueling is the correct recovery action to restore it to a usable state.

## Question 21
Why can a low-fuel vehicle not start a delivery?

Because a delivery should not begin if the vehicle does not have enough fuel to operate safely. Starting a delivery with low fuel would risk failure or immediate breakdown.

## Question 22
Why can a vehicle run out of fuel after delivery has already started?

Because travel consumes fuel over time, and the vehicle may not have enough fuel left to continue. The delivery can start, but the vehicle can still become empty during travel.

## Question 23
Why does cargo remain InTransit when its vehicle runs out of fuel?

Because the cargo is still in the middle of an active trip even though the vehicle can no longer continue. The delivery has not been completed, so the cargo should remain in transit until the system decides how to handle the failure.

## Question 24
Why can delivery completion fail when fuel is empty?

Because a completed delivery should only happen while the vehicle still has operational fuel. If the vehicle is empty, there is no valid basis to complete the shipment successfully.

## Question 25
Why must cancellation update both Cargo and Vehicle?

Because cancellation affects both the shipment and the vehicle assignment. If only one side is updated, the objects would disagree about the current state.

## Question 26
Why can an in-transit delivery not be cancelled?

Because once a shipment is already moving, canceling it would break the consistency of the active delivery process. The system should only allow cancellation before the delivery starts or while the cargo is still loaded but not yet in transit.

## Question 27
Why are query functions declared const?

Because they only read data and do not modify the object. Declaring them const makes the API safer and allows them to be called on constant objects.

## Question 28
Why does averageFuelLevel() need an empty-vector check?

Because dividing by zero would happen if there were no vehicles. The empty-vector check prevents invalid math and returns a safe default result of 0.0.

## Question 29
Why does the highest-capacity search preserve the earlier vehicle when values are equal?

Because the requirement says the earlier vehicle should be selected in a tie. Preserving the first match keeps the result stable and predictable.

## Question 30
What was the hardest state-consistency problem in this project?

The hardest problem was keeping Cargo and Vehicle in sync during loading, delivery, refueling, and cancellation. A small mistake in one object could leave the system in a contradictory state.

## Question 31
Describe one real bug you found.

Bug:
A vehicle could be added even when the ID already existed, because the duplicate check was inverted.

Cause:
The addVehicle() logic used the wrong condition for the ID lookup, so it accepted duplicates instead of rejecting them.

Fix:
I changed the check to require that the ID does not already exist before adding the vehicle.

What I learned:
I learned that duplicate checks must be written carefully and that a single inverted condition can break the whole object lifecycle.

## Question 32
What part of the design would you improve with another day?

I would improve the validation and error-handling design by adding clearer state transition rules and more explicit methods for each transition. That would make the project easier to extend and reduce the chance of inconsistent states in future changes.
