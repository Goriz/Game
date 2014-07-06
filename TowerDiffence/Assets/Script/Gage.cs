using UnityEngine;
using System.Collections;

public class Gage : MonoBehaviour {
	public float parcent = 1;
	private float scalex;

	// Use this for initialization
	void Start () {
		scalex = transform.localScale.x;
	}
	
	// Update is called once per frame
	void Update () {
	}

	public void gageControl(float parcent){

		transform.localScale = new Vector2 (scalex * parcent  , transform.localScale.y);

	}
}
