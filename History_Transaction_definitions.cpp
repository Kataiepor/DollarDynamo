#include <cassert>
#include <iomanip>
#include <iostream>

#include "project4.hpp"
#include "History.hpp"
#include "Transaction.hpp"

////////////////////////////////////////////////////////////////////////////////
// Definitions for Transaction class
////////////////////////////////////////////////////////////////////////////////
//
//

// Constructor
// TODO

Transaction::Transaction( std::string ticker_symbol,  unsigned int day_date,  
                          unsigned int month_date,  unsigned year_date, 
                          bool buy_sell_trans,  unsigned int number_shares,  
                          double trans_amount ){
          
          this -> symbol = ticker_symbol; 
          this -> day = day_date; 
          this -> month = month_date; 
          this -> year = year_date; 

          if (buy_sell_trans == true){

            this -> trans_type = "Buy";

          }

          else {

            this -> trans_type = "Sell"; 

          }

          this -> shares =  number_shares;  //(*this).shares = number_shares;
          this -> amount = trans_amount; 
          this -> p_next = nullptr; 
          this-> trans_id = this-> assigned_trans_id;
          this-> assigned_trans_id++;

          this->acb = 0;
          this->acb_per_share = 0;
          this->cgl = 0;
          this->share_balance = 0;
 

        }

// Destructor
// TODO
Transaction::~Transaction(){

}

// Overloaded < operator.
// TODO
bool Transaction::operator<( Transaction const &other ){

  if(this -> get_year() < other.get_year()){

    return true; 
  
  }

  if ((this -> get_year() == other.get_year()) && (this -> get_month() < other.get_month())){

    return true; 

  }

  if ((this -> get_year() == other.get_year()) && (this -> get_month() == other.get_month()) && (this -> get_day() < other.get_day())){

    return true; 

  }

  if ((this -> get_year() == other.get_year()) && (this -> get_month() == other.get_month()) && (this -> get_day() == other.get_day())){

    if ((this -> get_trans_id() < other.get_trans_id())){

      return true; 

    }

    else {

      return false; 

    }
  
  }

    return false; 

}

// GIVEN
// Member functions to get values.
//
std::string Transaction::get_symbol() const { return symbol; }
unsigned int Transaction::get_day() const { return day; }
unsigned int Transaction::get_month() const { return month; }
unsigned int Transaction::get_year() const { return year; }
unsigned int Transaction::get_shares() const { return shares; }
double Transaction::get_amount() const { return amount; }
double Transaction::get_acb() const { return acb; }
double Transaction::get_acb_per_share() const { return acb_per_share; }
unsigned int Transaction::get_share_balance() const { return share_balance; }
double Transaction::get_cgl() const { return cgl; }
bool Transaction::get_trans_type() const { return (trans_type == "Buy") ? true : false; }
unsigned int Transaction::get_trans_id() const { return trans_id; }
Transaction *Transaction::get_next() { return p_next; }

// GIVEN
// Member functions to set values.
//
void Transaction::set_acb(double acb_value) { acb = acb_value; }
void Transaction::set_acb_per_share(double acb_share_value) { acb_per_share = acb_share_value; }
void Transaction::set_share_balance(unsigned int bal) { share_balance = bal; }
void Transaction::set_cgl(double value) { cgl = value; }
void Transaction::set_next(Transaction *p_new_next) { p_next = p_new_next; }

// GIVEN
// Print the transaction.
//
void Transaction::print()
{
  std::cout << std::fixed << std::setprecision(2);
  std::cout << std::setw(4) << get_trans_id() << " "
            << std::setw(4) << get_symbol() << " "
            << std::setw(4) << get_day() << " "
            << std::setw(4) << get_month() << " "
            << std::setw(4) << get_year() << " ";

  if (get_trans_type())
  {
    std::cout << "  Buy  ";
  }
  else
  {
    std::cout << "  Sell ";
  }

  std::cout << std::setw(4) << get_shares() << " "
            << std::setw(10) << get_amount() << " "
            << std::setw(10) << get_acb() << " " << std::setw(4) << get_share_balance() << " "
            << std::setw(10) << std::setprecision(3) << get_acb_per_share() << " "
            << std::setw(10) << std::setprecision(3) << get_cgl()
            << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
// Definitions for the History class
////////////////////////////////////////////////////////////////////////////////
//
//

// Constructor
// TASK 3
//

History::History()
{
  // implement of constructor goes here
  p_head = nullptr;
}

// Destructor
// TASK 3
//

History::~History()
{
  Transaction *t = this->get_p_head();
  while (t != nullptr)
  {
    Transaction *temporary = t;
    t = t->get_next();
    delete temporary;
  }
}

// read_history(...): Read the transaction history from file.
// TASK 4
//

void History::read_history()
{
  ece150::open_file();
  bool isDone = false;
  ece150::next_trans_entry();
  while (!isDone)
  {
    Transaction *transaction = new Transaction(ece150::get_trans_symbol(),
                                               ece150::get_trans_day(), ece150::get_trans_month(), ece150::get_trans_year(), ece150::get_trans_type(), ece150::get_trans_shares(), ece150::get_trans_amount());

    this->insert(transaction);
    isDone = !ece150::next_trans_entry();
  }

  ece150::close_file();
}

// insert(...): Insert transaction into linked list.
// TASK 5
//

void History::insert(Transaction *p_new_trans)
{
  if (this->get_p_head() != nullptr)
  {
    Transaction *first = this->get_p_head();
    Transaction *second = nullptr;

    while (first != nullptr)
    {
      second = first;
      first = first->get_next();
    }

    second->set_next(p_new_trans);
  }
  else
  {
    p_head = p_new_trans;
  }
}

// sort_by_date(): Sort the linked list by trade date.
// TASK 6
//

void History::sort_by_date()
{
  Transaction *first = this->get_p_head();
  Transaction *new_head = nullptr;
  Transaction *new_temp = nullptr;

  while (first != nullptr)
  {
    if (new_head == nullptr)
    {
      new_head = first;
      this->p_head = this->get_p_head()->get_next();
      new_head->set_next(nullptr);
      first = this->get_p_head();
      continue;
    }

    if (*(first) < *(new_head))
    {
      this->p_head = this->get_p_head()->get_next();
      first->set_next(new_head);
      new_head = first;
      first = this->get_p_head();
      continue;
    }

    new_temp = new_head;

    while (new_temp != nullptr)
    {
      if (new_temp->get_next() == nullptr)
      {
        this->p_head = this->get_p_head()->get_next();
        new_temp->set_next(first);
        first->set_next(nullptr);
        first = this->get_p_head();
        break;
      }

      if (*(first) < *(new_temp->get_next()))
      {
        this->p_head = this->get_p_head()->get_next();
        first->set_next(new_temp->get_next());
        new_temp->set_next(first);
        first = this->get_p_head();
        break;
      }
      new_temp = new_temp->get_next();
    }
  }
  this->p_head = new_head;
  new_head = nullptr;
}

// update_acb_cgl(): Updates the ACB and CGL values.
// TASK 7
//

void History::update_acb_cgl()
{
  Transaction *first = this->get_p_head();
  Transaction *second = nullptr;

  while (first != nullptr)
  {

    if (second == nullptr){

      first->set_acb(first->get_amount());
      first->set_share_balance(first->get_shares());
      first->set_acb_per_share(first->get_acb() / first->get_share_balance());

    }

    else if (first->get_trans_type() == true){
      first->set_acb(second->get_acb() + first->get_amount());
      first->set_share_balance(second->get_share_balance() + first->get_shares());

      first->set_acb_per_share(first->get_acb() / first->get_share_balance());
    }

    else
    {
      first->set_acb(second->get_acb() - (first->get_shares() * second->get_acb_per_share()));
      first->set_share_balance(second->get_share_balance() - first->get_shares());
      first->set_acb_per_share(second->get_acb_per_share());
      first->set_cgl(first->get_amount() - (first->get_shares() * second->get_acb_per_share()));
    }

    second = first;
    first = first->get_next();
  }
}

// compute_cgl(): )Compute the ACB, and CGL.
// TASK 8

double History::compute_cgl(unsigned int year)
{
  Transaction *first = this->get_p_head();
  double result = 0.0;

  while (first != nullptr)
  {
    if (first->get_year() == year)
    {
      result = result + first->get_cgl();
    }

    first = first->get_next();
  }

  return result;
}

// print() Print the transaction history.
// TASK 9
//

void History::print()
{
  std::cout << "========== BEGIN TRANSACTION HISTORY ============" << std::endl;

  Transaction *t = p_head;

  while (t != nullptr)
  {
    t->print();
    t = t->get_next();
  }

  std::cout << "========== END TRANSACTION HISTORY ==============" << std::endl;
}

// GIVEN
// get_p_head(): Full access to the linked list.
//
Transaction *History::get_p_head() { return p_head; }