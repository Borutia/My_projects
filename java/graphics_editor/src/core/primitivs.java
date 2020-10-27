package core;

import java.awt.*;

public class primitivs {
    public static void line(int x1, int y1, int x2, int y2, Graphics2D g){
        g.setStroke(new BasicStroke(3.0f));
        g.drawLine(x1,y1,x2,y2);
    }

    public static void oval(int x1, int y1, int x2, int y2, Graphics2D g){
        g.setStroke(new BasicStroke(3.0f));
        g.drawOval(x1,y1,x2,y2);
    }

    public static void quad(int x1, int y1, int x2, int y2, Graphics2D g){
        g.setStroke(new BasicStroke(3.0f));
        g.drawRect(x1,y1,x2,y2);
    }
}
