import javax.swing.*;
import java.awt.*;

class Domik extends JFrame {
    // функция для создания окна для рисования
    Domik(String s) {
        super(s);
        setLayout(null);
        setSize(300, 350);
        setVisible(true);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
    }

    // функиця для рисования домика
    public void paint(Graphics g) {
        g.setColor(Color.BLACK);
        g.drawLine(50, 150, 125, 75);
        g.drawLine(125, 75, 200, 150);
        g.drawLine(50, 150, 200, 150);
        g.drawLine(200, 150, 200, 300);
        g.drawLine(200, 300, 50, 300);
        g.drawLine(50, 300, 50, 150);
        g.drawLine(75, 200, 125, 200);
        g.drawLine(125, 200, 125, 250);
        g.drawLine(125, 250, 75, 250);
        g.drawLine(75, 250, 75, 200);
        g.drawLine(150, 100, 150, 75);
        g.drawLine(150, 75, 175, 75);
        g.drawLine(175, 75, 175, 125);
        g.drawLine(145, 220, 185, 220);
        g.drawLine(145, 220, 145, 300);
        g.drawLine(185, 220, 185, 300);
        g.setColor(Color.BLUE);
        g.fillRect(145, 220, 40, 80);
        g.setColor(Color.YELLOW);
        g.fillRect(75, 200, 50, 50);
    }

    public static void main(String[] args) {
        // создаем домик
        new Domik("Домик");
    }
}