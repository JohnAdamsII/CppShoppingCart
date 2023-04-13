#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <string>

enum class ItemType
{
    MusicCD,
    Book,
    Magazine
};

class Item
{
public:
    Item(const std::string &name, double price, ItemType type) : name_(name), price_(price), type_(type) {}
    virtual ~Item() = default;
    virtual double getPrice() const { return price_; }
    const std::string &getName() const { return name_; }
    ItemType getType() const { return type_; }

protected:
    std::string name_;
    double price_;
    ItemType type_;
};

class MusicCD : public Item
{
public:
    MusicCD(const std::string &name, double price) : Item(name, price, ItemType::MusicCD) {}
    double getPrice() const override { return price_; }
};

class Book : public Item
{
public:
    Book(const std::string &name, double price) : Item(name, price, ItemType::Book) {}
    double getPrice() const override { return price_; }
};

class Magazine : public Item
{
public:
    Magazine(const std::string &name, double price) : Item(name, price, ItemType::Magazine) {}
    double getPrice() const override { return price_; }
};

class ShoppingCart
{
public:
    void addItem(std::unique_ptr<Item> item)
    {
        m_items.emplace_back(std::move(item));
    }

    void addItems(std::vector<std::unique_ptr<Item>> &items)
    {
        for (auto &item : items)
        {
            m_items.emplace_back(std::move(item));
        }
    }

    void writeContentsToFile(const std::string &filename)
    {
        std::ofstream file(filename);
        if (file.is_open())
        {
            for (const auto &item : m_items)
            {
                file << item->getName() << " - $" << item->getPrice() << std::endl;
            }
            file.close();
        }
    }

    void summarizeContents()
    {
        double totalCDs = 0;
        double totalBooks = 0;
        double totalMagazines = 0;
        double grandTotal = 0;
        int cdCount = 0, bookCount = 0, magazineCount = 0;

        for (const auto &item : m_items)
        {
            switch (item->getType())
            {
            case ItemType::MusicCD:
                totalCDs += item->getPrice();
                cdCount++;
                break;
            case ItemType::Book:
                totalBooks += item->getPrice();
                bookCount++;
                break;
            case ItemType::Magazine:
                totalMagazines += item->getPrice();
                magazineCount++;
                break;
            }
        }

        grandTotal = totalCDs + totalBooks + totalMagazines;

        std::cout << "Total CDs: " << cdCount << " - $" << totalCDs << std::endl;
        std::cout << "Total Books: " << bookCount << " - $" << totalBooks << std::endl;
        std::cout << "Total Magazines: " << magazineCount << " - $" << totalMagazines << std::endl;
        std::cout << "Grand Total: $" << grandTotal << std::endl;
    }

private:
    std::vector<std::unique_ptr<Item>> m_items;
};

int main()
{
    ShoppingCart cart;
    cart.addItem(std::make_unique<MusicCD>("A really cool CD", 10.99));
    cart.addItem(std::make_unique<Book>("A good book", 15.99));
    cart.addItem(std::make_unique<Magazine>("Cool Magazine", 7.99));

    std::vector<std::unique_ptr<Item>> items;
    items.push_back(std::make_unique<MusicCD>("Album 2", 12.99));
    items.push_back(std::make_unique<Book>("Book 2", 8.50));
    items.push_back(std::make_unique<Magazine>("Mag 2", 6.99));

    cart.addItems(items);
    cart.writeContentsToFile("shopping_cart_contents.txt");
    cart.summarizeContents();

    return 0;
}
