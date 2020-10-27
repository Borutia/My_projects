package window;
import core.*;
import javax.swing.*;

public class colors {
    public colors(mcolor color, MyFrame list){ // панелька для кнопок цвета
        JToolBar colorbar = new JToolBar("Colorbar", JToolBar.HORIZONTAL);
        colorbar.setBounds(200,0,list.getWidth(),60);
        colorsbuttons col = new colorsbuttons(colorbar, color);
        list.add(colorbar);
    }
}
