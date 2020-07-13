package com.example.Notes.model;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.validation.constraints.NotBlank;
import java.util.Objects;

@Entity
public class Note {
    @Id @GeneratedValue
    private long id;

    private String title;

    @NotBlank
    private String text;

    @Override
    public String toString() {
        return String.format(
                "Note[id=%d, title='%s', text='%s']",
                id, title, text);
    }

    public Note() {
    }

    public Note(long id, String title, String text) {
        this.id = id;
        this.title = title;
        this.text = text;
    }

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getText() {
        return text;
    }

    public void setText(String text) {
        this.text = text;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == this)
            return true;
        if (obj == null || obj.getClass() != getClass() )
            return false;
        Note note = (Note) obj;
        return id == note.id &&
                title.equals(note.title) &&
                text.equals(note.text);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id, title, text);
    }
}
