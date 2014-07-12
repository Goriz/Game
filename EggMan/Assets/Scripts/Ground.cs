using UnityEngine;
using System.Collections;

public class Ground : MonoBehaviour {


	public GameObject Break;
	// Use this for initialization
	void OnCollisionEnter2D(Collision2D c) {

		//Destroy (c.gameObject);
		//Instantiate (Break, c.transform.position, c.transform.rotation);

	}
}
