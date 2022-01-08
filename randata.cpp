#include "randata.h"



randata::randata(){


  gen = mt19937(rd());

  d = normal_distribution<> (60,15);
}
 
string randata::first_names[86] = {"Liam","Noah", "Oliver","Elijah","William","James","Benjamin","Lucas","Henry","Alexander","Mason","Michael","Ethan","Daniel","Jacob","Logan","Jackson","Levi","Sebastian","Mateo","Jack","Owen","Theodore","Aiden","Samuel","Joseph","John","David","Wyatt","Matthew","Luke","Asher","Carter","Julian","Grayson","Leo","Jayden","Gabriel","Isaac","Lincoln","Anthony","Hudson","Dylan","Ezra","Thomas","Charles","Christopher","Jaxon","Maverickk","Josiah","Isaiah","Andrew","Elias","Joshua","Nathan","Caleb","Ryan","Adrian","Miles","Eli","Nolan","Christian","Aaron","Cameron","Ezekiel","Colton","Luca","Landon","Hunter","Jonathan","Santiago","Axel","Easton","Cooper","Jeremiah","Angel","Roman","Connor","Jameson","Robert","Greyson","Jordan","Ian","Carson","Jaxson","Leonardo"};



string randata::last_names[50] = {"Smith", "Johnson", "Williams", "Brown", "Jones", "Garcia", "Miller", "Davis", "Rodriguez", "Martinez", "Hernandez", "Lopez", "Gonzalez", "Wilson", "Anderson", "Thomas", "Taylor", "Moore", "Jackson", "Martin", "Lee", "Perez", "Thompson", "White", "Harris", "Sanchez", "Clark", "Ramirez", "Lewis", "Robinson", "Walker", "Young", "Allen", "King", "Wright", "Scott", "Torres","Nguyen", "Hill", "Flores", "Green", "Adams", "Nelson", "Baker", "Hall", "Rivera", "Campbell", "Mitchell", "Carter", "Roberts"};




string randata::adjectives[100] = {"Abrupt", "Acidic", "Adorable", "Adventurous", "Aggressive", "Agitated", "Alert", "Aloof", "Bored", "Brave", "Bright", "Colossal", "Condescending", "Confused", "Cooperative", "Corny", "Costly", "Courageous", "Cruel", "Despicable", "Determined", "Dilapidated", "Diminutive", "Distressed", "Disturbed", "Dizzy", "Exasperated", "Excited", "Exhilarated", "Extensive", "Exuberant", "Frothy", "Frustrating", "Funny", "Fuzzy", "Gaudy", "Graceful", "Greasy", "Grieving", "Gritty", "Grotesque", "Grubby", "Grumpy", "Handsome", "Happy", "Hollow", "Hungry", "Hurt", "Icy", "Ideal", "Immense", "Impressionable", "Intrigued", "Irate", "Foolish", "Frantic", "Fresh", "Friendly", "Frightened", "Frothy", "Frustrating", "Glorious", "Gorgeous", "Grubby", "Happy", "Harebrained", "Health", "Helpful", "Helpless", "High", "Hollow", "Homely", "Large", "Lazy", "Livid", "Lonely", "Loose", "Lovely", "Lucky", "Mysterious", "Narrow", "Nasty", "Outrageous", "Panicky", "Perfect", "Perplexed", "Quizzical", "Teeny", "Tender", "Tense", "Terrible", "Tricky", "Troubled", "Unsightly", "Upset", "Wicked", "Yummy", "Zany", "Zealous", "Zippy"};


  
  
string randata::nouns[85] = {"Ovens", "Speakers", "Tea", "Poets", "Salads", "Fortunes", "Men", "Beers", "Problems", "Funerals", "Bedrooms", "Cabinets", "Moods", "Payments", "Cells", "Poetry", "Genes", "Youths", "Energy", "News", "Meat", "Pizzas", "Sisters", "Surgeries", "Art", "Penalties", "Mixtures", "Clients", "Bread", "People", "Villages", "Libraries", "Farmers", "Products", "Guests", "Ducks", "Cows", "Lions", "Giraffes", "Gorillas", "Tomatoes", "Fruit", "Vegetables", "Snakes", "Lizards", "Geckos", "Professors", "Mountains", "Trees", "Rivers", "Pants", "Socks", "Shirts", "Bagels", "Dogs", "Cats", "Cows", "Pigs", "Corn", "Fish", "Elephants", "Tigers", "Leopards", "Bananas", "Apples", "Snowmen", "Penguins", "Pirates", "Dreidels", "Latkes", "Pies", "Cakes", "Cupcakes", "Oranges", "Bread", "Balls", "Vikings", "Trophies", "Birds", "Worms", "Trees", "Leaves", "Branches", "Glasses", "Arms"};




string randata::wrestler_name(){
  return first_names[rand() %86] + " " +last_names[rand() % 50];
}

string randata::team_name(){
  return adjectives[rand() %100] + " " + nouns[rand() % 50];
}

randata::~randata(){
}
						  
