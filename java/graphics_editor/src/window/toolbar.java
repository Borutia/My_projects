package window;

import javax.swing.*;
import java.awt.*;

public class toolbar {
    public toolbar(MyFrame list, start rez){
        JToolBar toolBar = new JToolBar("Toolbar", JToolBar.VERTICAL);
        toolbarbuttons buttons = new toolbarbuttons(toolBar, rez);
        toolBar.setBounds(0,60,200,400);
        JLabel instr = new JLabel("Инструменты");
        instr.setBounds(10,10,100,20);
        toolBar.add(instr);
        JLabel prim = new JLabel("Примитивы");
        prim.setBounds(10,160,100,20);
        toolBar.add(prim);
        list.add(toolBar);
        toolBar.setLayout(null);
    }

}
