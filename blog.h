#pragma once
#include<unordered_set>
#include<vector>
#include<string>
#include<chrono>

class commit {
private:
    static int cnt;
public:
    int id;
    std::string content;
    int user_id;
    int father_id = 0;
    int blog_id;
    std::chrono::year_month_day date;
public:
    commit() { 
        id = ++cnt; //实现自增id
        date = floor<std::chrono::days>(std::chrono::system_clock::now());
    }
    commit(int blog_id, int user_id, int father_id) : blog_id(blog_id), user_id(user_id), father_id(father_id) { 
        id = ++cnt; 
        date = floor<std::chrono::days>(std::chrono::system_clock::now());
    }
};

class blog
{
private:
    static int cnt;
public:
	int id;
	std::string title;
	std::string content;
	int author_id;
	std::chrono::year_month_day date;
    std::unordered_set<int> likes;//点赞id列表，防止重复点赞


    std::chrono::year_month_day getCurrentDate();
public:
    blog() { 
        id = ++cnt; 
        this->date = getCurrentDate();
    }
    blog(int id, std::string title, std::string content, int author_id, int y, int m, int d)
        : id(id), title(title), content(content), author_id(author_id), 
        date(std::chrono::year_month_day(std::chrono::year(y), std::chrono::month(m), std::chrono::day(d))) {}

    blog(std::string title, std::string content, int author_id)
        : title(title), content(content), author_id(author_id) {
        this->date = getCurrentDate();
        id = ++cnt;
    }

    void setDate(std::chrono::year_month_day date);



    friend std::ostream& operator<<(std::ostream& os, const blog& _Blog) {
        os << _Blog.id << " " << _Blog.title << " " << _Blog.content << " " << _Blog.author_id
            << " " << _Blog.date.year() << " " << _Blog.date.month() << " " << _Blog.date.day();
        return os;
    }
    friend std::istream& operator>>(std::istream& is, blog& _Blog) {
        using namespace::std::chrono;
        int y, m, d;
        is >> _Blog.id >>  _Blog.title >> _Blog.content >> _Blog.author_id >> y >> m >> d;
        _Blog.setDate(year_month_day(year(y), month(m), day(d)));
        return is;
    }
};
