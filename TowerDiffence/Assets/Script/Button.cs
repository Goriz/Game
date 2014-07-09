using UnityEngine;
using System.Collections;

public class Button : MonoBehaviour {

	void OnGUI()
	{
		Rect rect = new Rect(50, 50, 100, 50);
		bool isClicked = GUI.Button(rect, "GAME START");
		if (isClicked)
		{
			print("Stand by Ready!");
			Application.LoadLevel ("TowerDiffence");
		}
	}
}
