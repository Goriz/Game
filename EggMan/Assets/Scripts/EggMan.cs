using UnityEngine;
using System.Collections;

public class EggMan : MonoBehaviour {


	public GameObject eggman;

	public GameObject Break;

	// Update is called once per frame
	void Update () {
		//if (Input.GetMouseButtonDown(0)){
		if (Input.touchCount > 0){

			//Vector3 v = Input.mousePosition;
			//Vector2 egg = eggman.transform.position;
			//v.z = 10;
		    //v = Camera.main.ScreenToWorldPoint(v);

			Vector3 v = Input.GetTouch(0).position;
			Vector2 egg = eggman.transform.position;
			v.z = 10;
			v = Camera.main.ScreenToWorldPoint(v);

			//Debug.Log(v);
			//Debug.Log(Input.mousePosition);
			//Debug.Log(eggman.transform.localPosition);
			if( v.x >= egg.x-0.5 && v.x <=egg.x+0.5 && v.y >= egg.y-0.5 && v.y <= egg.y+0.5){
				Destroy (eggman);
				Instantiate (Break, eggman.transform.position, eggman.transform.rotation);
			}

		}
	}
}
