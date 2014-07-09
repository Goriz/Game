using UnityEngine;
using System.Collections;

public class Player : MonoBehaviour {
	public GameObject fire;
	public GameObject[] mpstars;
	private Vector2 tappoint;
	private Animator animator;


	// Use this for initialization
	void Start () {
		animator = GetComponent<Animator> ();
	}
	
	// Update is called once per frame
	void Update () {
	
		if (Input.GetMouseButtonDown (0)) {

			tappoint = Camera.main.ScreenToWorldPoint(Input.mousePosition);

			if(GameObject.Find("MPStar10") != null){
				Destroy(GameObject.Find("MPStar10"));
			}else if(GameObject.Find("MPStar9") != null){
				Destroy(GameObject.Find("MPStar9"));
			}else if(GameObject.Find("MPStar8") != null){
				Destroy(GameObject.Find("MPStar8"));
			}else if(GameObject.Find("MPStar7") != null){
				Destroy(GameObject.Find("MPStar7"));
			}else if(GameObject.Find("MPStar6") != null){
				Destroy(GameObject.Find("MPStar6"));
			}else if(GameObject.Find("MPStar5") != null){
				Destroy(GameObject.Find("MPStar5"));
			}else if(GameObject.Find("MPStar4") != null){
				Destroy(GameObject.Find("MPStar4"));
			}else if(GameObject.Find("MPStar3") != null){
				Destroy(GameObject.Find("MPStar3"));
			}else if(GameObject.Find("MPStar2") != null){
				Destroy(GameObject.Find("MPStar2"));
			}else if(GameObject.Find("MPStar1") != null){
				Destroy(GameObject.Find("MPStar1"));
			}

			animator.SetTrigger ("Attack");
			Instantiate (fire, transform.position, transform.rotation);

				}


	}


	public Vector2 getMousePoint(){
		return tappoint;
	}
}
