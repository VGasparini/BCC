package biblioteca;

public class Item {
    public Midia item;
    @Override
    public String toString() {
        return item.getNome();
    }
    public Item(Midia m) {
        item = m;
    }
}
