using UnityEngine;
using System.Collections;

public class Menu : MonoBehaviour {
	public GameObject chase;
	public GameObject chased;
	private GameObject title;

	// Use this for initialization
	void Start () {
		 title = GameObject.Find ("Title");
	}



	// Update is called once per frame
	void Update () {
		if (Input.GetMouseButtonDown (0)) {
			audio.Play();
			title.SetActive (false);
			GetComponent<Menu>().enabled = false;
			Application.LoadLevelAdditive ("StageSelect");

		}

	}
}
