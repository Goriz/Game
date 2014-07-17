using UnityEngine;
using System.Collections;

public class EggMan : MonoBehaviour {


	public GameObject eggman;
	public GameObject Break;
	public int point;


	//private int i=1;

	// Update is called once per frame
	void Update () {
		//Touch tch = Input.GetTouch(0);
		//Debug.Log (tch);
		//if (Input.GetMouseButtonDown(0)){
		if (Input.touchCount > 0 ){
			Touch tch = Input.GetTouch(0);
			if(tch.phase == TouchPhase.Began){

				//Vector3 v = Input.mousePosition;
				//Vector2 egg = eggman.transform.position;
				//v.z = 10;
			    //v = Camera.main.ScreenToWorldPoint(v);
				//Touch tch = Input.GetTouch(0);
				Vector3 v = tch.position;
				Vector2 egg = eggman.transform.position;
				v.z = 10;
				v = Camera.main.ScreenToWorldPoint(v);

				//Debug.Log(v);
				//Debug.Log(Input.mousePosition);
				//Debug.Log(eggman.transform.localPosition);
				if( v.x >= egg.x-0.8 && v.x <=egg.x+0.8 && v.y >= egg.y-0.8 && v.y <= egg.y+0.8){
					Destroy (eggman);
					FindObjectOfType<Score>().AddPoint(point);
					Instantiate (Break, eggman.transform.position, eggman.transform.rotation);
				}
			}
		}
	}
}
