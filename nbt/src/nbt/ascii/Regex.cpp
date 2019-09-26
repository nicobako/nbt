#include <nbt/ascii/Regex.hpp>

namespace nbt {
namespace ascii {
Tokens split(std::string const & line, std::string const & delimiters) {
  std::string search_string = "([^" + delimiters + "]+)";
  std::regex re(search_string);

  auto words_begin = std::sregex_iterator(line.begin(), line.end(), re);

  auto words_end = std::sregex_iterator();

  Tokens tokens;

  for (auto & i = words_begin; i != words_end; i++) {
    tokens.emplace_back(i->str());
  }

  return tokens;
}

Tokens search(std::string const & line, std::string const & regex) {
  std::regex re(regex);
  std::smatch sm;

  std::regex_search(line, sm, re);

  return Tokens(sm.begin(), sm.end());
}

Tokens match(std::string const & line, std::string const & regex) {
  std::regex re(regex);
  std::smatch sm;

  std::regex_match(line, sm, re);

  return Tokens(sm.begin(), sm.end());
}

std::vector<Tokens>
find_all(std::string const & line, std::string const & regex) {
  std::regex re(regex);

  auto res_begin = std::sregex_iterator(line.begin(), line.end(), re);

  auto res_end = std::sregex_iterator();

  std::vector<Tokens> results;

  for (auto & i = res_begin; i != res_end; i++) {
    results.push_back(Tokens(i->begin(), i->end()));
  }

  return results;
}

std::string replace(
    std::string const & line,
    std::string const & regex,
    std::string const & format) {
  std::string result;
  std::regex_replace(
      std::back_inserter(result),
      line.begin(),
      line.end(),
      std::regex(regex),
      format);

  return result;
}

void trim(std::string & line, std::string const & characters) {
  if (line.empty())
    return;

  auto trimmed_line = nbt::ascii::match(
      line, "[" + characters + "]*" + "(.*?)[" + characters + "]*");

  line = trimmed_line.at(1);
}
} // namespace ascii
} // namespace nbt
