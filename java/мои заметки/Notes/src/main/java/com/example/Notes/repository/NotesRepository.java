package com.example.Notes.repository;

import com.example.Notes.model.Note;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.CrudRepository;
import org.springframework.data.repository.query.Param;
import java.util.List;

public interface NotesRepository extends CrudRepository<Note, Long> {

    List<Note> findAll();

    @Query(value = "SELECT * FROM note WHERE LOWER(title) LIKE CONCAT('%', :search, '%') " +
            "OR LOWER(text) LIKE CONCAT('%', :search, '%')", nativeQuery = true)
    List<Note> findByText(@Param("search") String text);
}


