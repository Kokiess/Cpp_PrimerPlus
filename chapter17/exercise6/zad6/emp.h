#pragma once
#include <iostream>
#include <string>
#include <fstream>

namespace choices
{
	enum classkind { Employee, Manager, Fink, Highfink };
}


class abstr_emp
{
private:
	std::string fname;
	std::string lname;
	std::string job;
public:
	abstr_emp() : fname(""), lname(""), job("") {}
	abstr_emp(const std::string& fn, const std::string& ln, const std::string& j) : fname(fn), lname(ln), job(j) {}
	virtual void ShowAll() const;
	virtual void SetAll();
	virtual void Writeall(std::ofstream& fout);
	virtual void Readall(std::ifstream& fin);
	friend std::ostream& operator << (std::ostream& os, const abstr_emp& e);
	virtual ~abstr_emp() = 0;
};

class employee : public abstr_emp
{
public:
	employee() : abstr_emp() {}
	employee(const std::string& fn, const std::string& ln, const std::string& j) : abstr_emp(fn, ln, j) {}
	virtual void ShowAll() const;
	virtual void SetAll();
	virtual void Writeall(std::ofstream& fout);
	virtual void Readall(std::ifstream& fin);
};

class manager : virtual public abstr_emp
{
private:
	int inchargeof;
protected:
	int InChargeOf() const { return inchargeof; }
	int& InChargeOf() { return inchargeof; }
public:
	manager() : abstr_emp(), inchargeof(0) {}
	manager(const std::string& fn, const std::string& ln, const std::string& j, int ico = 0)
		: abstr_emp(fn, ln, j), inchargeof(ico) {}
	manager(const abstr_emp& e, int ico) : abstr_emp(e), inchargeof(ico) {}
	manager(const manager& m);
	virtual void ShowAll() const;
	virtual void SetAll();
	virtual void Writeall(std::ofstream& fout);
	virtual void Readall(std::ifstream& fin);
};

class fink : virtual public abstr_emp
{
private:
	std::string reportsto;
protected:
	const std::string ReportsTo() const { return reportsto; }
	std::string& ReportsTo() { return reportsto; }
public:
	fink() : abstr_emp(), reportsto("") {}
	fink(const std::string& fn, const std::string& ln, const std::string& j,
		const std::string& rpo) : abstr_emp(fn, ln, j), reportsto(rpo) {}
	fink(const abstr_emp& e, const std::string& rpo) : abstr_emp(e), reportsto(rpo) {}
	fink(const fink& f);
	virtual void ShowAll() const;
	virtual void SetAll();
	virtual void Writeall(std::ofstream& fout);
	virtual void Readall(std::ifstream& fin);
};

class highfink : public manager, public fink
{
public:
	highfink() : abstr_emp(), fink(), manager() {}
	highfink(const std::string& fn, const std::string& ln, const std::string& j,
		const std::string& rpo, int ico) : abstr_emp(fn, ln, j), fink(fn, ln, j, rpo),
		manager(fn, ln, j, ico) {}
	highfink(const abstr_emp& e, const std::string& rpo, int ico) : abstr_emp(e),
		fink(e, rpo), manager(e, ico) {}
	highfink(const fink& f, int ico) : abstr_emp(f), fink(f), manager(f, ico) {}
	highfink(const manager& m, const std::string& rpo) : abstr_emp(m), manager(m),
		fink(m, rpo) {}
	highfink(const highfink& h);
	virtual void ShowAll() const;
	virtual void SetAll();
	virtual void Writeall(std::ofstream& fout);
	virtual void Readall(std::ifstream& fin);
};

std::ifstream& operator >> (std::ifstream& is, choices::classkind& ck);