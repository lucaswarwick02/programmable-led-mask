using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;

public class DisplayManager : MonoBehaviour
{
    int[,] display = new int[4, 23];
    int offset_1 = 4;
    int offset_2 = 2;
    int offset_3 = 3;
    int offset_4 = 2;

    public void WriteToFile () {
        string path = "function.txt";
        // Write text
        StreamWriter writer = new StreamWriter(path, true);
        writer.WriteLine("Test");
        writer.WriteLine("Test 2");
        writer.Close();
    }
}
