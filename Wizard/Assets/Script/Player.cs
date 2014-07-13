using UnityEngine;
using System.Collections;

public class Player : MonoBehaviour {
	public GameObject fire;
	private GameObject command;
	private GameObject MPStarController;
	private Vector2 tappoint;
	private Animator animator;
	private int ChargeId;
	public bool charge = false;



	// Use this for initialization
	void Start () {
		animator = GetComponent<Animator> ();

		ChargeId = Animator.StringToHash ("Charge");

		command = GameObject.Find("Command");

		MPStarController = GameObject.Find("MPStarController");
	}
	
	// Update is called once per frame
	void Update () {
	

		if (Input.GetMouseButtonDown (0)) {
			tappoint = Camera.main.ScreenToWorldPoint(Input.mousePosition);

			Raycast();

			if(charge == false && tappoint.x > -3.5 && GameObject.Find("MPStar1") != null){
			animator.SetTrigger ("Attack");
			Instantiate (fire, transform.position, transform.rotation);
				audio.Play();
				FindObjectOfType<MPStar>().Shot();
			}
		}

		if (charge == true) {
			animator.SetBool(ChargeId, true);
			command.SetActive(true);
		}else{
			animator.SetBool(ChargeId, false);
			command.SetActive(false);
		}
	}


	public Vector2 getMousePoint(){
		return tappoint;
	}

	public bool getCharge(){
		return charge;
	}


	void Raycast(){
		Collider2D collition2d = Physics2D.OverlapPoint(tappoint);
		if (collition2d) {
			RaycastHit2D hitObject = Physics2D.Raycast(tappoint,-Vector2.up);
			if (hitObject) {
				Debug.Log("hit object is " + hitObject.collider.gameObject.name);
				if(hitObject.collider.gameObject.name == "Player"){
					if(charge == false){
					charge = true;
					}else charge = false;
				}
			}
		}
	}

	void OnTriggerEnter2D(Collider2D c){
		FindObjectOfType<Score>().Save();
		Application.LoadLevel("GameOver");
		
	}

}
