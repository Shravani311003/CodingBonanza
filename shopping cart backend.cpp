#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
using namespace std;

//Product, Items, Cart

//Forward Declarations
class Items;
class Cart;

class Product{
    int id;
    string name;
    int price;
    public:
    //Assignments List
    Product(){}
    Product(int u_id,string name,int price){
        id=u_id;
        this->name=name;
        this->price=price;
    }
    string DisplayProduct(){
        return name+" : "+to_string(price)+"\n";
    }
    string getShortName(){
        return name.substr(0,1);
    }
    friend class Items;
    friend class Cart;
};

class Items{

    Product product; //const value is fixed and cannot be changed
    int quantity;
    public:
    //constructor using init list 
    Items(){}
    Items(Product p,int q):product(p),quantity(q){}

    int getItemPrice(){
        return product.price * quantity; // price is private and so in order to access we will use friend class
    }

    string getItemInfo(){
        return product.name + " x " + to_string(quantity) + " : Rs. " + to_string(quantity*product.price)+"\n";
    }
    friend class Cart;
};

class Cart{
    unordered_map<int,Items> items;
    public :
    void addProduct(Product product)
    {
        if(items.count(product.id) == 0)
        {
            Items newItems(product,1);
            items[product.id] = newItems;
        }else{
            items[product.id].quantity+=1;
        }
    }
    int getTotal(){
        int total=0;
        for(auto itemPair : items)
        {
            auto item=itemPair.second;
            total+=(item.product.price*item.quantity);
        }
        return total;
    }
    string viewCart(){
        if(items.empty())
        {
            return "Cart is empty";
        }
        string itemList;
        int cart_total=getTotal();

        for(auto itemPair : items){
            auto item=itemPair.second;
            itemList.append(item.getItemInfo());
        }

        return itemList+"\nTotal Amount : Rs. "+to_string(cart_total)+"\n";
    }

    bool isEmpty(){
        return items.empty();
    }
};


vector<Product> allProducts = {
    Product(1,"apple",26),
    Product(2,"mango",46),
    Product(3,"guava",36),
    Product(4,"orange",86),
    Product(5,"kiwi",66),
};

Product* chooseProduct(){
    string productList;
    cout<<"Available products :"<<"\n";
    for(auto product : allProducts) {
      productList.append(product.DisplayProduct());
    }
    cout<<productList<<"\n";
    cout<<"----------------------"<<"\n";
    string choice;
    cin>>choice;
    for(int i=0;i<allProducts.size();i++) {
        if(allProducts[i].getShortName()==choice) {
            return &allProducts[i];
        }
    }
    cout<<"Product not found"<<endl;
    return NULL;
};

bool checkout(Cart &cart){
    if(cart.isEmpty())
    {
        return false;
    }
    int total=cart.getTotal();
    cout<<"Total: "<<total<<endl;
    cout<<"Pay in Cash: ";
    int paid;
    cin>>paid;
    if(paid>=total)
    {
        cout<<"Change received: "<<(paid-total)<<endl;
    }
    else if(paid<total){
    cout<<"Paid Successful: "<<paid<<endl;
    cout<<"Please clear your due :"<<(total-paid)<<endl;    
    }
    cout<<"Thank you for shopping with us!"<<endl;
    return true;
};
int main()
{
    char action;
    Cart cart;
    while(true)
    {
         cout<<"Select an action - (a)dd item , (r)emove item, (d)elete all item in cart, (v)iew cart, (c)heckout "<<"\n";
        cin >> action;
        if(action == 'a')
        {
            Product* p = chooseProduct();
            if(p!=NULL)
            {
                cout<<"Item added to cart: "<<endl;
                cart.addProduct(*p);
            }
        }
        else if(action == 'v')
        {
            cout<<"----------------"<<"\n";
            cout<<cart.viewCart()<<endl;
            cout<<"------------------"<<"\n";
        }
        else if(action == 'c')
        {
            cart.viewCart();
           if(checkout(cart))
           {
            break;
           }
        }
    }
   
    return 0;
}
