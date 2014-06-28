using UnityEngine;
using System.Collections;

public class Menu : MonoBehaviour {
	public GameObject chase;
	public GameObject chased;


	// Use this for initialization
	void Start () {
		
	}



	// Update is called once per frame
	void Update () {
		if (Input.GetMouseButtonDown (0)) {
			Application.LoadLevel ("TowerDiffence");
		}

	}
}
