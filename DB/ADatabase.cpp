///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <DB/ADatabase.hpp>



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::db::ADatabase::ADatabase(
    ::std::string name,
    ::std::string path
)
    : m_name{ name }
{
    if (::sqlite3_open(::std::string{ path + m_name + ".csv" }.c_str(), &m_db) != SQLITE_OK) {
        throw ::std::runtime_error{ "Cannot open database: "s + m_name };
    }
}

///////////////////////////////////////////////////////////////////////////
::db::ADatabase::~ADatabase()
{
    sqlite3_close(m_db);
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Operations
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::db::ADatabase::addEntry(
    ::std::string type,
    ::std::string name
)
{
    return this->alter("ADD", name + " "s + type);
}

///////////////////////////////////////////////////////////////////////////
void ::db::ADatabase::deleteEntry(
    ::std::string name
)
{
    return this->alter("DROP COLUMN", name);
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Helpers
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::db::ADatabase::alter(
    ::std::string action,
    ::std::string code
)
{
    this->executeCode(::std::string{"ALTER TABLE Products"s + action + " "s + code + ";" });
}

///////////////////////////////////////////////////////////////////////////
void ::db::ADatabase::insertInto(
    ::std::vector<::std::string> names,
    ::std::vector<::std::string> values
)
{
    ::std::string namesStr;
    for (auto& str : names) {
        namesStr += str + ", ";
    }
    namesStr = namesStr.substr(0, namesStr.size() - 2);

    ::std::string valuesStr;
    for (auto& str : values) {
        valuesStr += str + ", ";
    }
    valuesStr = valuesStr.substr(0, valuesStr.size() - 2);

    this->executeCode(::std::string{
        "INSERT INTO Products("s + namesStr + ")"s + "VALUES ("s + valuesStr + ");"
    });
}

///////////////////////////////////////////////////////////////////////////
void ::db::ADatabase::executeCode(
    ::std::string sqlCode
)
{
    if (char* errPtr; ::sqlite3_exec(m_db, sqlCode.c_str(), nullptr, nullptr, &errPtr) != SQLITE_OK) {
        ::std::string errMsg{ errPtr };
        ::sqlite3_free(errPtr);
        throw ::std::runtime_error{ "Error executing DB code:\n\n" + sqlCode + "\n\n\t"s + errMsg };
    }
}
