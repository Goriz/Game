using UnityEngine;
using System.Collections;

public class MenuEnemy : MonoBehaviour {
	public int speed = 1;
	public bool chase = true;
	private GameObject player = null;


	// Use this for initialization
	void Start () {
		player = GameObject.Find("MenuPlayer");

		// lifeTime秒後に削除
		Destroy (gameObject, 9);
	}
	
	// Update is called once per frame
	void Update () {
		if (chase == true) {
			transform.position = Vector2.MoveTowards (transform.position, new Vector2 (-8, 0) , speed * Time.deltaTime);
		}
		if (chase == false) {
			transform.position = Vector2.MoveTowards (transform.position, new Vector2 (6, 0), speed * Time.deltaTime);
		}
	}
}
