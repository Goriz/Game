using UnityEngine;
using System.Collections;

public class Menu : MonoBehaviour {

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		

	}

	void GameStart(){
		FadeManager.Instance.LoadLevel("Battle",1.0f);
	}

}
