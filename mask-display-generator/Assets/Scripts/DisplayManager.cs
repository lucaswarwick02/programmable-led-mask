using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.IO;
using System;

public class DisplayManager : MonoBehaviour
{
    bool[,] display = new bool[4, 23];
    int[] offsets = {5, 3, 4, 3};

    public GameObject row1;
    List<Image> row1_images = new List<Image>();
    public GameObject row2;
    List<Image> row2_images = new List<Image>();
    public GameObject row3;
    List<Image> row3_images = new List<Image>();
    public GameObject row4;
    List<Image> row4_images = new List<Image>();
    public Sprite on;
    public Sprite off;

    private void Start() {
        foreach (Transform obj in row1.transform) {
            row1_images.Add(obj.GetComponent<Image>());
        }
        foreach (Transform obj in row2.transform) {
            row2_images.Add(obj.GetComponent<Image>());
        }
        foreach (Transform obj in row3.transform) {
            row3_images.Add(obj.GetComponent<Image>());
        }
        foreach (Transform obj in row4.transform) {
            row4_images.Add(obj.GetComponent<Image>());
        }
    }

    public void WriteToFile () {
        string path = "function.txt";
        // Write text
        StreamWriter writer = new StreamWriter(path, false);

        // Start of Function
        writer.WriteLine("void generatedFunction () {");
        writer.WriteLine("  wipe();");
        for (int row = 0; row < 4; row++) {
            writer.WriteLine("  // Row " + (row + 1) );
            for (int led = 0; led < 23; led++) {
                if (display[row, led]) {
                    writer.WriteLine("  setLED(" + (row + 1) + ", " + (led + offsets[row]) + ");");
                }
            }

        }
        // Close Function
        writer.WriteLine("  FastLED.show();");
        writer.WriteLine("}");

        writer.Close();
    }

    public void toggleRow1(int led) {
        display[0, 22 - led] = !display[0, 22 - led];
        if (display[0, 22 - led]) {
            row1_images[led].sprite = on;
        }
        else {
            row1_images[led].sprite = off;
        }
    }

    public void toggleRow2(int led) {
        display[1, 22 - led] = !display[1, 22 - led];
        if (display[1, 22 - led]) {
            row2_images[led].sprite = on;
        }
        else {
            row2_images[led].sprite = off;
        }
    }

    public void toggleRow3(int led) {
        display[2, 22 - led] = !display[2, 22 - led];
        if (display[2, 22 - led]) {
            row3_images[led].sprite = on;
        }
        else {
            row3_images[led].sprite = off;
        }
    }

    public void toggleRow4(int led) {
        display[3, 22 - led] = !display[3, 22 - led];
        if (display[3, 22 - led]) {
            row4_images[led].sprite = on;
        }
        else {
            row4_images[led].sprite = off;
        }
    }
}
