using UnityEngine;
using System.Collections;

public class MenuPlayer : MonoBehaviour {
	public int speed = 1;
	public bool chase = true;
	private GameObject enemy = null;

	// Use this for initialization
	void Start () {
		enemy = GameObject.Find("MenuEnemy");

		Destroy (gameObject, 8);
	}
	
	// Update is called once per frame
	void Update () {
		if (chase == true) {
		transform.position = Vector2.MoveTowards (transform.position, enemy.transform.position , speed * Time.deltaTime);
				}
		if (chase == false) {
			transform.position = Vector2.MoveTowards (transform.position, new Vector2 (-6, 0), speed * Time.deltaTime);
				}
	}
}
