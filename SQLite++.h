#include <string>
#include <iostream>

namespace sqlite {

class database
{
  public:

	database(const std::string & filename);
	database(const database & db);
	~database();

	database operator =(const database &);
    
    void execute(const std::string &);

	friend class statement;

  private:
	database();

	struct database_i *implementation;
};

typedef enum {
	null,
	text,
	integer,
	real,
	date,
	blob} type;

class value
{
  public:

	value();
	value(const char *);
	value(const std::string &);
	value(long long);
	value(double);
	value(const value &);
	~value();

	value & operator =(const value &);

	type getType() const;
	std::string asText() const;
	long long asInteger() const;
	double asReal() const;

	std::ostream & print(std::ostream &) const;

  private:
	struct value_i *implementation;
};

class statement
{
  public:

	statement(database &, const std::string &);
	~statement();

	void bind(int index, const value & v);
    void bind(const value & v);
	bool step();
	void execute();

	int columns() const;
	value column(unsigned int) const;
	value column(const std::string &) const;

	value operator[](unsigned int) const;
	value operator[](const std::string &) const;
	
  private:

	statement();
	statement(const statement &);
	statement & operator =(const statement &);

	struct statement_i *implementation;
};

}; // namespace sqlite
