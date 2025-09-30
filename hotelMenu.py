# features: display menu, order item, order another item, total bill
import os

def clear_screen():
    os.system('cls')

menu = {
    "Pizza" : 250,
    "Burger" : 150,
    "Pasta" : 200,
    "Fries" : 100,
    "Coke" : 50,
    "Juice" : 100
}

def display_menu():
    clear_screen()
    print("=" * 40)
    print("Welcome to our Restaurant!")
    print("Here is our menu:")
    print("\n-- Enter item name to order --")
    print("\n" + "=" * 40)
    print("Item\t\t\tPrice")
    print("----\t\t\t-----")
    for item, price in menu.items():
        print(f"{item}\t\t\t{price}")
    print("=" * 40 + "\n")

def take_order():
    clear_screen()
    print("=" * 40 + "\n")
    print("Place your order:")
    print("=" * 40 + "\n")
    order = {}
    
    
    display_menu()  # Show the menu first
    
    # First order
    user_input = input("Please enter your first order from the menu: ").strip().title()
    if user_input in menu:
        add_item_to_order(order, user_input)
    else:
        print("Invalid item. Please choose from the menu.")
        return order

    while True:
        clear_screen()
        print("Available options:\n")
        print("-- Type 'done' to finish the order --")
        print("-- Type 'menu' to see the menu again --")
        print("-- Type 'check' to see current order --")
        print("-- Type 'cancel' to remove an item --\n")

        user_input = input("Please select an option: ").strip().title()
        clear_screen()

        if user_input == 'Done': 
            break
        elif user_input == 'Menu':
            while True:
                display_menu()
                menu_input = input("\nEnter item name to order (or press Enter to return to options): ").strip().title()
                if menu_input == "":
                    break
                elif menu_input in menu:
                    add_item_to_order(order, menu_input)
                    input("\nPress Enter to continue ordering from menu...")
                else:
                    print("\nInvalid item. Please choose from the menu.")
                    input("Press Enter to try again...")
            clear_screen()
        elif user_input == 'Check':
            display_current_order(order)
            input("Press Enter to return to options...")
            clear_screen()
        elif user_input == 'Cancel':
            cancel_item(order)
        elif user_input in menu:
            add_item_to_order(order, user_input)
        else:
            print("Invalid option. Please try again.")

    return order

def add_item_to_order(order, item):
    try:
        quantity = int(input(f"\nHow many {item} would you like to order?\n"))
        clear_screen()

        if quantity == 0:
            print("Please enter a valid quantity.")
            return
        
        if item in order:
            order[item] += quantity
        else:
            order[item] = quantity

        print(f"Added {quantity} {item}(s) to your order.")
        display_current_order(order)

    except ValueError:
        print("Invalid input. Please enter a number for quantity.")

def cancel_item(order):
    if not order:
        clear_screen()
        print("You haven't ordered anything yet. Nothing to cancel.")
        return

    display_current_order(order)
    item_to_cancel = input("Enter the item name you want to cancel: ").strip().title()


    if item_to_cancel in order:
        current_quantity = order[item_to_cancel]
        try:
            cancel_quantity = int(input(f"How many {item_to_cancel}(s) would you like to remove? (Current quantity: {current_quantity}): "))
            clear_screen()
            
            if cancel_quantity <= 0:
                print("Please enter a valid quantity (greater than 0).")
            elif cancel_quantity > current_quantity:
                print(f"You only have {current_quantity} {item_to_cancel}(s) in your order.")
            else:
                order[item_to_cancel] -= cancel_quantity
                if order[item_to_cancel] == 0:
                    del order[item_to_cancel]
                print(f"Removed {cancel_quantity} {item_to_cancel}(s) from your order.")
                if item_to_cancel in order:
                    print(f"Remaining {item_to_cancel}(s): {order[item_to_cancel]}")
                display_current_order(order)
        
        except ValueError:
            print("Invalid input. Please enter a number for quantity.")

def display_current_order(order):
    if not order:
        print("You haven't ordered anything yet.")
        return
    
    print("\n" + "=" * 40)
    print("Your current order:")
    print("=" * 40)
    total = 0
    for item, quantity in order.items():
        item_total = menu[item] * quantity
        total += item_total
        print(f"{item} x{quantity} : {menu[item]}tk each = {item_total}tk")

    print(f"\nCurrent Total: {total}tk")
    print("=" * 40 + "\n")

def display_bill(order):
    if not order:
        print("No items ordered.")
        return
    
    print("\n" + "=" * 40)
    print("Final Bill:")
    print("=" * 40)

    total = 0
    for item, quantity in order.items():
        item_total = menu[item] * quantity
        total += item_total
        print(f"{item} x{quantity} : {menu[item]}tk each = {item_total}tk")

    print("=" * 40)
    print(f"Total Bill: {total}tk")
    print("=" * 40 + "\n")
    print("\n\nThank you for visiting our Restaurant!\n")
    print("=" * 40 + "\n")


def main():
    display_menu()
    order = take_order()
    display_bill(order)

if __name__ == "__main__":
    main()