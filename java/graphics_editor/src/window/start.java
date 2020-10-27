package window;
import core.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import static core.instruments.*;
import static core.primitivs.*;

public class start {
    private MyPanel list;
    private boolean pressed = false;
    private int xPad;
    private int yPad;
    private int xf;
    private int yf;

    int rez = 0;
    public static BufferedImage imag;
    public static boolean loading = false;

    public void getrez(int a){
        this.rez = a;
    }
    public start()
    {
        Font font = new Font("Arial", Font.PLAIN, 12);
        loadimage img = new loadimage();
        imag = img.getImag();
        mcolor maincolor = new mcolor();

        MyFrame win = new MyFrame("graf-edit");
        win.setSize(1000,700);
        win.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        list = new MyPanel();
        list.setBounds(200,60,320,320);
        list.setBackground(Color.white);
        list.setOpaque(true);
        win.add(list);

        menubar menu = new menubar(list,win);
        toolbar tool = new toolbar(win, this);
        colors col = new colors(maincolor, win);

        JLabel label = new JLabel("fdfsgdfg");
        label.setFont(font);
        


        list.addMouseMotionListener(new MouseAdapter() {
            @Override
            public void mouseDragged(MouseEvent e) {
                if(pressed==true)
                {
                    Graphics g = imag.getGraphics();
                    Graphics2D g2d = (Graphics2D)g;
                    g2d.setColor(maincolor.getMaincolor());
                    switch(rez)
                    {
                        case 0:
                            pen(xPad, yPad, e.getX(), e.getY(), g2d);
                            break;
                        case 1:
                            brush(xPad, yPad, e.getX(), e.getY(), g2d);
                            break;
                        case 2:
                            lastik(xPad, yPad, e.getX(), e.getY(), g2d);
                            break;
                    }
                    xPad = e.getX();
                    yPad = e.getY();
                }
                list.repaint();
            }
        });

        list.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                Graphics g = imag.getGraphics();
                Graphics2D g2d = (Graphics2D)g;
                g2d.setColor(maincolor.getMaincolor());
                switch (rez)
                {
                    case 0:
                        pen(xPad, yPad, xPad+1, yPad+1, g2d);
                        break;

                    case 1:
                        brush(xPad, yPad, xPad+1, yPad+1, g2d);
                        break;
                    case 2:
                        lastik(xPad, yPad, xPad+1, yPad+1, g2d);
                        break;
                    case 3:
                        list.requestFocus();
                        break;
                }
                xPad=e.getX();
                yPad=e.getY();

                pressed = true;
                list.repaint();
            }
            public void mousePressed(MouseEvent e){
                xPad=e.getX();
                yPad=e.getY();
                xf = e.getX();
                yf = e.getY();
                pressed = true;
            }
            @Override
            public void mouseReleased(MouseEvent e){
                Graphics g = imag.getGraphics();
                Graphics2D g2d = (Graphics2D)g;
                g2d.setColor(maincolor.getMaincolor());
                int x1=xf, x2 = xPad, y1 = yf, y2 = yPad;
                if(xf>xPad){x2=xf; x1=xPad;}
                if(yf>yPad){y2=yf; y1 = yPad;}
                switch (rez)
                {
                    case 4:
                        line(xf,yf, e.getX(), e.getY(), g2d);
                        break;
                    case 5:
                        oval(x1,y1,(x2-x1),(y2-y1), g2d);
                        break;
                    case 6:
                        quad(x1,y1,(x2-x1),(y2-y1), g2d);
                        break;
                }
                xf=0; yf=0;
                pressed = false;
                list.repaint();
            }
        });

        list.addKeyListener(new KeyAdapter() {
            @Override
            public void keyTyped(KeyEvent e) {
                if(rez==3){
                    Graphics g = imag.getGraphics();
                    Graphics2D g2d = (Graphics2D)g;
                    g2d.setColor(maincolor.getMaincolor());
                    g2d.setStroke(new BasicStroke(2.0f));

                    String str = new String("");
                    str+=e.getKeyChar();
                    g2d.setFont(new Font("Arial", 0, 15));
                    g2d.drawString(str, xPad, yPad);
                    xPad+=8;
                    list.requestFocus();
                    list.repaint();
                }
            }

            @Override
            public void keyReleased(KeyEvent e) {
                list.requestFocus();
            }
        });

        win.addComponentListener(new ComponentAdapter() {
            @Override
            public void componentResized(ComponentEvent e) {
                if(loading==false){
                    list.setSize(win.getWidth()-40, win.getHeight()-80);
                    BufferedImage img = new BufferedImage(list.getWidth(),list.getHeight(),BufferedImage.TYPE_INT_RGB);
                    Graphics2D d2 = (Graphics2D) img.createGraphics();
                    d2.setColor(Color.white);
                    d2.fillRect(0,0,list.getWidth(), list.getHeight());
                    img.setData(imag.getRaster());
                    imag=img;
                    list.repaint();
                }
                loading=false;
            }
        });

        win.setLayout(null);
        win.setVisible(true);
    }


}
