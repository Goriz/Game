using UnityEngine;
using System.Collections;

public class Fire : MonoBehaviour {
	public float speed = 5f;
	private Vector2 director;

	// Use this for initialization
	void Start () {
		director = FindObjectOfType<Player> ().getMousePoint ();
	}
	
	// Update is called once per frame
	void Update () {
		transform.position = Vector2.MoveTowards (transform.position, director, speed * Time.deltaTime);


		if (transform.position.x == director.x) {
			Destroy(gameObject);

			}
	}

	void OnTriggerEnter2D(Collider2D c){
		//Destroy(gameObject);
		
	}
}
