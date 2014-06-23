using UnityEngine;
using System.Collections;

public class Gage : MonoBehaviour {

	// Use this for initialization
	void Start () {
		transform.localScale = new Vector2 (transform.localScale.x / 2, transform.localScale.y);
	}
	
	// Update is called once per frame
	void Update () {
	}
}
