#include "blog.h"

int commit::cnt = 0;
int blog::cnt = 0;
void blog::setDate(std::chrono::year_month_day date)
{
    this->date = date;
}

std::chrono::year_month_day blog::getCurrentDate()
{
    return floor<std::chrono::days>(std::chrono::system_clock::now());
}
