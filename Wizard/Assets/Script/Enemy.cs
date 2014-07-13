using UnityEngine;
using System.Collections;

public class Enemy : MonoBehaviour {

	public float speed = 1f;
	private Vector2 director;
	private Animator animator;

	// Use this for initialization
	void Start () {
		director = new Vector2 (-4f, 0);
		animator = GetComponent<Animator> ();
	}
	
	// Update is called once per frame
	void Update () {
		transform.position = Vector2.MoveTowards (transform.position, director, speed * Time.deltaTime);

	}

	void OnTriggerEnter2D(Collider2D c){
		audio.Play ();
		director = transform.position;
		animator.SetTrigger ("Dead");

	}

	void Dead(){
		FindObjectOfType<Score>().AddPoint(1);
		Destroy (gameObject);

	}
}
