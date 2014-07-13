using UnityEngine;
using System.Collections;

public class EnemyCreator : MonoBehaviour {

	public GameObject enemy;
	public float seconds = 5f;
	private int count = 0;

	public const float INTERVAL = 10.0f;
	public float timer = INTERVAL;
	
	// Startメソッドをコルーチンとして呼び出す
	IEnumerator Start ()
	{

		while (true) {

			int rand = Random.Range(1, 4);
			
			switch(rand){
			case 1:
				transform.position = new Vector2 (6, Random.Range (-4f, 5f));
				Instantiate (enemy, transform.position, transform.rotation);
				break;
			case 2:
				transform.position = new Vector2 (Random.Range (0, 7f), 4);
				Instantiate (enemy, transform.position, transform.rotation);
				break;
			case 3:
				transform.position = new Vector2 (Random.Range (0, 7f), -4);
				Instantiate (enemy, transform.position, transform.rotation);
				break;
			default:
				break;
			}

			count++;

			// seconds秒待つ
			yield return new WaitForSeconds (seconds);
			
		}
	}

	private void Update()
	{
		timer -= Time.deltaTime;
		if (timer <= 0)
		{
			if(seconds > 1.0f){
			seconds = seconds - 0.5f;
			}
			timer = INTERVAL;
		}
	}
}
