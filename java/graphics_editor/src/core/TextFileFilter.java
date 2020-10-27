package core;

import javax.swing.filechooser.FileFilter;

public class TextFileFilter extends FileFilter {
    private String str;
    public TextFileFilter(String str){
        this.str=str;
    }
    @Override
    public boolean accept(java.io.File file) {
        if(file.isDirectory())return true;
        return (file.getName().endsWith(str));
    }

    @Override
    public String getDescription() {
        return "*"+str;
    }
}
