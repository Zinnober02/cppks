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
        id = ++cnt; //ʵ������id
        date = floor<std::chrono::days>(std::chrono::system_clock::now());
    }
    commit(int blog_id, int user_id, int father_id) : blog_id(blog_id), user_id(user_id), father_id(father_id) { 
        id = ++cnt; 
        date = floor<std::chrono::days>(std::chrono::system_clock::now());
    }


    friend std::ostream& operator<<(std::ostream& os, const commit& c) {
        os << c.id << " " << c.content << " " << c.user_id << " " << c.father_id << " " << c.blog_id << " " <<
            c.date.year() << " " << static_cast<unsigned>(c.date.month()) << " " << c.date.day();
        return os;
    }
    friend std::istream& operator>>(std::istream& is, commit& c) {
        using namespace::std::chrono;
        int y, m, d;
        is >> c.id >> c.content >> c.user_id >> c.father_id >> c.blog_id >> y >> m >> d;
        c.date = year_month_day(year(y), month(m), day(d));
        return is;
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
    std::unordered_set<int> likes;//����id�б���ֹ�ظ�����


    std::chrono::year_month_day getCurrentDate();
public:
    blog() { 
        id = ++cnt; 
        this->date = getCurrentDate();
    }
    blog(int id, std::string title, std::string content, int author_id, int y, int m, int d)
        : id(id), title(title), content(content), author_id(author_id), 
        date(std::chrono::year_month_day(std::chrono::year(y), std::chrono::month(m), std::chrono::day(d))) {}

    blog(std::string title, std::string content, int author_id, std::unordered_set<int> likes)
        : id(id), title(title), content(content), author_id(author_id), likes(likes) {
        this->date = getCurrentDate();
        id = ++cnt;
    }

    blog(std::string title, std::string content, int author_id)
        : title(title), content(content), author_id(author_id) {
        this->date = getCurrentDate();
        id = ++cnt;
    }

    void setDate(std::chrono::year_month_day date);

    friend std::ostream& operator<<(std::ostream& os, const blog& _Blog) {
        os << _Blog.id << " " << _Blog.title << " " << _Blog.content << " " << _Blog.author_id << " " << 
            _Blog.date.year() << " " << static_cast<unsigned>(_Blog.date.month()) << " " << _Blog.date.day();
        for (auto& like : _Blog.likes) {
            os << " " << like;
        }
        return os;
    }
    friend std::istream& operator>>(std::istream& is, blog& _Blog) {
        using namespace::std::chrono;
        int y, m, d;
        is >> _Blog.id >>  _Blog.title >> _Blog.content >> _Blog.author_id >> y >> m >> d;
        _Blog.setDate(year_month_day(year(y), month(m), day(d)));
        int tmp;
        while (is >> tmp)
            _Blog.likes.emplace(tmp);
        return is;
    }
};
