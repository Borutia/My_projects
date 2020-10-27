package window;

import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;

public class MyPanel extends JPanel {
    public MyPanel(){}
    public void paintComponent(Graphics g){
        BufferedImage imag1 = start.imag;
        if(imag1 == null)
        {
            imag1 = new BufferedImage(this.getWidth(), this.getHeight(), BufferedImage.TYPE_INT_RGB);
            start.imag = imag1;
            Graphics2D g2d = (Graphics2D) imag1.createGraphics();
            g2d.setColor(Color.white);
            g2d.fillRect(0,0,this.getWidth(),this.getHeight());
        }
        super.paintComponent(g);
        g.drawImage(imag1,0,0,this);
    }
}
