/*****************************************
** File:    Shop.cpp
** Project: CMSC 202 Project 2, spring 2023
** Author:  Abdullah sufian
** Date:    3/9/23
** Section: 43
** E-mail:  asufian1@umbc.edu 
** Description: This is a C++ class for a shop. It includes functions to add, get, increment, and decrement ingredients, as well as functions to calculate and get the shop's rank based on the number of
 ingredients it has. The file includes a constructor that sets some default values for the shop.
** 
**
**
***********************************************/


#include "Shop.h"
#include <iostream>
using namespace std;


//test shop
Shop::Shop() {
  m_shopName = "Test";
  m_numIngredients = 0;
  m_shopRank = 'F';
}


//Shop
// Define a class called "Shop" with a constructor that takes a string argument "name"
Shop::Shop(string name) {

  // Set the private member variable m_shopName to the provided name
  m_shopName = name;

  // Initialize the private member variable m_numIngredients to 0
  m_numIngredients = 0;

  // Initialize the private member variable m_shopRank to the default value of 'F'
  // This variable presumably represents the quality ranking of the shop
  // Since this code doesn't include any logic for changing the rank, it will always be 'F'
  m_shopRank = 'F';
}


//GetName
//Getter for the name for the shop
string Shop::GetName() {

  return m_shopName;

}

//SetName
//Sets the name by getting the user input of what they call the shop
void Shop::SetName(string name) {

  m_shopName = name;

}


//IngredientCount
// This function counts the number of ingredients in the shop's inventory
// that have a quantity greater than zero.
int Shop::IngredientCount() {
  int count = 0; // declare count var

  //loops throught num of ingredients and gets the count of the ingredient if greater than 0
  for (int i = 0; i < m_numIngredients; i++) { 

    // If the quantity of the ingredient is greater than zero, increment the count variable
    if (m_myIngredients[i].m_quantity > 0) {
      count++;
    }
  }

  // Return the count of ingredients that have a quantity greater than zero
  return count;
}


//GetIngredient
// This function returns an ingredient from the shop's inventory based on its index.
// If the index is out of bounds, an empty ingredient is returned instead.
Ingredient Shop::GetIngredient(int index) {

  // Check if the index is out of bounds
  if (index < 0 || index >= m_numIngredients) {

    // If the index is out of bounds, create and return an empty ingredient
    //  ALWAYS SET VALUES TO A DEFAULT
    Ingredient emptyIngredient;
    emptyIngredient.m_name = "";
    emptyIngredient.m_type = "";        
    emptyIngredient.m_ingredient1 = ""; 
    emptyIngredient.m_ingredient2 = "";
    emptyIngredient.m_quantity = 0;
    return emptyIngredient;
  }

  //return the index of ingredient if its in bounds
  return m_myIngredients[index];

}


//AddIngredient
void Shop::AddIngredient(Ingredient ingredient) {

  //check to see if ingredient exists in shop
  int index = CheckIngredient(ingredient);

  //if ingredient not in shop (out of bounds) add the ingredient
  if(index == -1){
    
  m_myIngredients[m_numIngredients] = ingredient;
  m_myIngredients[m_numIngredients].m_quantity = 0;

  // add +1
  m_numIngredients++;
  
  }
  
}

//IncrementQuantity
//This function checks if an Ingredient exists and increment the ingredients quantity by one if ingrdient is added or found
void Shop::IncrementQuantity(Ingredient ingredient) {

  // Checks if Ingredient exists
  int index = CheckIngredient(ingredient);

  //if it doesnt exists then it will add the ingredient
  if(index == -1){
    
      AddIngredient(ingredient);

      //increments the now added ingredient
      index = CheckIngredient(ingredient);
      m_myIngredients[index].m_quantity++;
      
    }

  //if it does exists than incremenrs the ingredient
  else{

    m_myIngredients[index].m_quantity++;
    
  }
  
}


// DecrementQuantity
// This function decrements the quantity of an ingredient in the shop's inventory by one.
bool Shop::DecrementQuantity(Ingredient ingredient) {
  
  // loop through the num of ingredients and when name is found decrement it
  for (int i = 0; i < m_numIngredients; i++) {
    
    //checks for the ingredient name and if its greater than 0
    if (m_myIngredients[i].m_name == ingredient.m_name) {
      
      if (m_myIngredients[i].m_quantity > 0) {
	
        // If the input ingredient is not found in the shop's inventory, return false 
        m_myIngredients[i].m_quantity--;
        return true;
        

	
      } else {
	// If the current ingredient's quantity is zero, return false
        return false;
      }
    }
  }

  // If the input ingredient is not found in the shop's inventory, return false
  return false;
}

//CheckIngredient
// This function takes an Ingredient object as input and checks if it is in the Shop's list of ingredients.
int Shop::CheckIngredient(Ingredient ingredient){
  
  //goes through num of ingredients and checks if the ingredient is in it
  for (int i = 0; i < m_numIngredients; i++){

    // If the ingredient is found in the list, return its index.
    if (m_myIngredients[i].m_name == ingredient.m_name) {
      return i;
    }
}
    // quits if not found
    return -1;
  }



//CheckQuantity
// This function checks if two ingredients exist in the shop and have a quantity greater than or equal to 1
bool Shop::CheckQuantity(Ingredient ingredient1, Ingredient ingredient2) {
  
  //Checks if both if the ingredient exists
  int indexOne = CheckIngredient(ingredient1);
  int indexTwo = CheckIngredient(ingredient2);

  //if it does not exist itll quit
   if (indexOne == -1){
     
    return false;

   }
   
   if (indexTwo == -1){
    return false;

   }
   
   // if its also less than one than itll return false
   if (m_myIngredients[indexOne].m_quantity < 1){
     
    return false;
   }
   
   if (m_myIngredients[indexTwo].m_quantity < 1){
     
    return false;
  }
   
  // if does have quantity return true
  return true;
  
}


//GetRank
//calculates and returns the rank of the shop.
char Shop::GetRank() {
  CalcRank();
  return m_shopRank;
}

// This function calculates the rank of a shop based on the number of ingredients it has
void Shop::CalcRank() {
int ingredientCount = IngredientCount();
int rankPercent = 0;

// Check if the project size is 0, if so, print an error message and return
if (PROJ2_SIZE == 0){
cout << "Invalid Project Size is 0" << endl;
return;
}

// Calculate the rank percentage if there are ingredients
if (ingredientCount > 0) {
rankPercent = 100 * ingredientCount / PROJ2_SIZE;
}

// Determine the shop rank based on the rank percentage
if (rankPercent < RANK_D) {
  m_shopRank = 'F';
} else if (rankPercent < RANK_C) {
  m_shopRank = 'D';
} else if (rankPercent < RANK_B) {
  m_shopRank = 'C';
} else if (rankPercent < RANK_A) {
  m_shopRank = 'B';
} else if (rankPercent < RANK_S) {
  m_shopRank = 'A';
} else {
  m_shopRank = 'S';
}
}


//ShopScore
//prints out information about the shop including its name, available products, the number of products in the shop with at least one quantity
//the percentage of available products found in the shop, and the shop's rank.
void Shop::ShopScore() {
  CalcRank();
  //prints out name of shop
  cout << endl << m_shopName << "'s Shop:" << endl;
  cout << "=========================" << endl;
  //the amount of total possible available products
  cout << "There are " << PROJ2_SIZE << " available products." <<endl;
  // The amount of ingredients that are in the shop and has atleast one quantity
  cout << "This shop has " << IngredientCount()<< " products in shop" << endl;
  //sets precision for percentage and calcs percentage.
  cout << fixed << setprecision(2);
  cout << "Percentage found: " << (double)IngredientCount() / PROJ2_SIZE * 100 << "%" << endl;
  // Prints the rank
  cout << "Rank: " << GetRank() << endl;
  cout << "=========================" << endl << endl;
}
