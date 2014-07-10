using UnityEngine;
using System.Collections;

public class MPStar : MonoBehaviour {

	public GameObject mpstar;	
	public int mpspeed = 3;
	
	private int starNumber = 0;
	private int mp = 0;


	void Update(){
		transform.position = new Vector2(-4.5f, -2.7f + 0.4f * starNumber);

		if (Input.GetMouseButtonDown (0)) {
			CreateStar();
		}
	}
	
	void CreateStar(){

		Instantiate (mpstar, transform.position, transform.rotation);
		starNumber++;
	}
	
	
	void UpButtonPressed() {
		print ("UpButton Pressed!");
		mp++;
		if (mp % mpspeed == 0) {
			CreateStar();
		}
	}
	
	void DownButtonPressed() {
		print ("DownButton Pressed!");
		mp++;
		if (mp % mpspeed == 0) {
			CreateStar();
		}
	}
	
	/// <summary>右ボタン押された</summary>
	void RightButtonPressed() {
		print ("RightButton Pressed!");
		mp++;
		if (mp % mpspeed == 0) {
			CreateStar();
		}
	}
	
	/// <summary>左ボタン押された</summary>
	void LeftButtonPressed() {
		print ("LeftButton Pressed!");
		mp++;
		if (mp % mpspeed == 0) {
			CreateStar();
		}
	} 

}
