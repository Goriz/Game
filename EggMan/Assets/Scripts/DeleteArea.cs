using UnityEngine;
using System.Collections;

public class DeleteArea : MonoBehaviour {

	// Use this for initialization
	void OnTriggerExit2D (Collider2D c)
	{
		Destroy (c.gameObject);
	}
}
