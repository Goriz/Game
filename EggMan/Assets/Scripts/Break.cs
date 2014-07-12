using UnityEngine;
using System.Collections;

public class Break : MonoBehaviour {

	// Use this for initialization
	//void Start () {
	
	//}
	
	// Update is called once per frame
	void OnAnimationFinish ()
	{
		Destroy (gameObject);
	}
}
