package com.example.Notes.service;

import com.example.Notes.exception.NotesException;
import com.example.Notes.model.Note;
import com.example.Notes.repository.NotesRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.dao.DataAccessException;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class NotesService {

    private NotesRepository notes;

    @Autowired
    public NotesService(NotesRepository notes) {
        this.notes = notes;
    }

    public List<Note> allNotes() {
        return notes.findAll();
    }

    public Note addNotes(Note note){
        Note SavedNotes = notes.save(note);
        return SavedNotes;
    }

    public void deleteNotes(long id) throws NotesException {
        try {
            notes.deleteById(id);
        } catch (DataAccessException e) {
            throw new NotesException(e.getMessage());
        }
    }

    public List<Note> find(String search) {
        return notes.findByText(search);
    }
}
