#pragma once

#include <string>

class Mission {
private:
    std::string name_;
    int priority_;

public:
    Mission();
    Mission(const std::string& name, int priority);

    const std::string& getName() const;
    int getPriority() const;
};
