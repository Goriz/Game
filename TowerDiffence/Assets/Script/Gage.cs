using UnityEngine;
using System.Collections;

public class Gage : MonoBehaviour {
	public float parcent = 1;

	// Use this for initialization
	void Start () {
	}
	
	// Update is called once per frame
	void Update () {
	}

	public void gageControl(int parcent){

		transform.localScale = new Vector2 (transform.localScale.x * parcent  , transform.localScale.y);

	}
}
