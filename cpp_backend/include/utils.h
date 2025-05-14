// utils.h

enum class Mode {
    Random, 
    Solve, 
    Invalid 
};

Mode parse_mode(const std::string& mode_str);
bool is_digits(const std::string& s);
std::string join_args(const std::vector<std::string>& args);

