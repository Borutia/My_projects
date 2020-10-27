package core;

import javax.swing.*;
import java.awt.*;

public class instruments {

    public static void pen(int x1, int y1, int x2, int y2, Graphics2D g){
        g.drawLine(x1, y1, x2, y2);
    }

    public static void brush(int x1, int y1, int x2, int y2, Graphics2D g){
        g.setStroke(new BasicStroke(3.0f));
        g.drawLine(x1,y1,x2,y2);
    }

    public static void lastik(int x1, int y1, int x2, int y2, Graphics2D g){
        g.setStroke(new BasicStroke(5.0f));
        g.setColor(Color.white);
        g.drawLine(x1,y1,x2,y2);
    }

}
