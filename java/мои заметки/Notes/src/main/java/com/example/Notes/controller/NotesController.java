package com.example.Notes.controller;

import com.example.Notes.exception.NotesException;
import com.example.Notes.model.Note;
import com.example.Notes.service.NotesService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.*;

import javax.validation.Valid;

@Controller
public class NotesController {

    private NotesService notes;

    @Autowired
    public NotesController(NotesService notes) {
        this.notes = notes;
    }

    @RequestMapping(value = "/", method = RequestMethod.GET)
    public String allNotes(Model model) {
        model.addAttribute("notes", notes.allNotes());
        return "notes";
    }

    @RequestMapping(value = "/", method = RequestMethod.POST)
    public String addNote(@Valid Note note, BindingResult bindingResult, Model model) {
        if (bindingResult.hasErrors()) {
            model.addAttribute("errors", bindingResult.getAllErrors());
            return "textError";
        }
        notes.addNotes(note);
        return "redirect:/";
    }

    @RequestMapping(value = "/remove/{id}")
    public String removeNote(@PathVariable("id") long id) {
        notes.deleteNotes(id);
        return "redirect:/";
    }

    @RequestMapping(value = "/find")
    public String findNotes(@RequestParam("query") String query, Model model) {
        model.addAttribute("search", query);
        model.addAttribute("notes", notes.find(query));
        return "notes";
    }

    @ExceptionHandler(NotesException.class)
    public String handleException(Exception e, Model model) {
        model.addAttribute("message", e.getMessage());
        return "applicationError";
    }

}
