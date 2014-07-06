using UnityEngine;
using System.Collections;

public class GagePlayer : MonoBehaviour {
	public float parcent = 1;
	private float scalex;

	GameObject player = null;

	// Use this for initialization
	void Start () {
		scalex = transform.localScale.x;

		player = GameObject.Find("Player");
	}
	
	// Update is called once per frame
	void Update () {
		transform.position = Vector2.MoveTowards (transform.position, new Vector2 (player.transform.position.x -0.35f, player.transform.position.y + 0.4f),
		                                          5f * Time.deltaTime);
	}

	public void gageControl2(float parcent){
		
		transform.localScale = new Vector2 (scalex * parcent  , transform.localScale.y);
		
	}
}
