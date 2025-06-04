package org.example.Model;

import org.junit.jupiter.api.Test;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

public class TestField {



    @Test
    public void testSetFeild() {
        Field field = new Field();
        int data;
        field.setField(5);
        data = field.field.size();
        assertEquals(25, data);
    }

    @Test
    public void testBoundary() {
        Field field = new Field();
        field.setField(4);
        assertTrue(field.boundary(4));
    }

    @Test
    public void testFillingField() {
        Field field = new Field();
        field.setField(5);
        field.fillingField(5);
        assertEquals(5, field.countOfBomb);
    }

    @Test
    public void testOpenAndCheckingForZero() {
        Field field = new Field();
        field.setField(5);
        field.fillingField(0);
        field.OpenAndCheckingForZero(0);
        assertEquals("0", field.field.get(1).getValue());
    }

    @Test
    public void testOpenAround() {
        Field field = new Field();
        field.setField(5);
        field.fillingField(0);
        field.OpenAround(0);
        assertEquals("0", field.field.get(1).getValue());
    }

    @Test
    public void testOpenAllCells() {
        Field field = new Field();
        field.setField(5);
        field.fillingField(0);
        field.openAllCell();
        assertEquals("0", field.field.get(1).getValue());
    }

    @Test
    public void testIsWin() {
        Field field = new Field();
        field.setField(5);
        field.fillingField(0);
        field.openAllCell();
        assertTrue(field.isWin());
    }

    @Test
    public void testIsNotWin() {
        Field field = new Field();
        field.setField(5);
        field.fillingField(0);
        assertFalse(field.isWin());
    }

    @Test
    public void testOpenTheCell() {
        Field field = new Field();
        field.setField(5);
        field.fillingField(0);
        field.openTheCell("Open 0");
        assertEquals("0", field.field.get(0).getValue());
    }

    @Test
    public void testPutTheFlag() {
        Field field = new Field();
        field.setField(5);
        field.fillingField(0);
        field.openTheCell("Flag 0");
        assertTrue(field.field.get(0).isFlagOpen());
    }




}
