  auto foo = [&arg1, &arg2](std::string arg3, std::string &arg4) {
    try {
      void *h = bar(arg3);
      if (h != nullptr) {
        arg4 = arg3;
        return 1;
      }
    } catch (...) {}

    for (auto &s : arg1) {
      std::ostringstream os;
      os << s << arg2 << arg3;
      if (cat(os.str().c_str()) == 0) {
        arg4 = os.str().c_str();
        return 1;
      }
    }
    return 0;
  };

  auto x = foo("String", sample) == 0;

// Lambda function 2 args => returns smallest

auto custom_min = [] (int x, int y) {
    int minimum = y;
    if (x < y) { 
        minimum = x;
    }
    return minimum;
};