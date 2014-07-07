using UnityEngine;
using System.Collections;

public class GameStart : MonoBehaviour {

	private FadeManager manager;

	private bool isClick = false;

	// Use this for initialization
	void Start () {
		manager = FindObjectOfType<FadeManager>();
	}
	
	void OnClick(){
		if(!isClick){
			isClick = true;
			manager.LoadLevel("Prepare",1.0f);
		}
	}
}
