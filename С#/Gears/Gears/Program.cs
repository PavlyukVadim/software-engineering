using System;
using System.Collections.Generic;

namespace Gears
{
	class MainClass
	{

		static void InitData(ref int numberOfGears, ref int numberOfConnections, ref int[,] arrayOfConnections, ref int[] arrayOfDirectionsOfVertices)
		{
			Console.WriteLine ("Enter number of gears: ");
			numberOfGears = Convert.ToInt32 (Console.ReadLine ());

			arrayOfDirectionsOfVertices = new int[numberOfGears];
			for (int i = 0; i < arrayOfDirectionsOfVertices.Length; i++) 
			{
				arrayOfDirectionsOfVertices [i] = -1;
			}

			Console.WriteLine ("Enter number of connections: ");
			numberOfConnections = Convert.ToInt32 (Console.ReadLine ());
			arrayOfConnections = new int[numberOfConnections, 2];
			for (int i = 0; i < arrayOfConnections.GetLength (0); i++) 
			{
				string tooltip;
				tooltip = String.Format("You are entering gears of {0} connection: ", i + 1);
				Console.WriteLine(tooltip);

				Console.WriteLine ("Enter first gear: ");
				arrayOfConnections [i, 0] = Convert.ToInt32 (Console.ReadLine ());

				Console.WriteLine ("Enter second gear: ");
				arrayOfConnections [i, 1] = Convert.ToInt32 (Console.ReadLine ());
			}
			Console.WriteLine (arrayOfConnections.GetLength(1));
		}


		static void otputAdjacencyMatrix(int[,] adjacencyMatrix) {
			Console.WriteLine("AdjacencyMatrix: ");
			for (int i = 0; i < adjacencyMatrix.GetLength (0); i++) 
			{
				for (int j = 0; j < adjacencyMatrix.GetLength (1); j++) 
				{
					Console.Write(adjacencyMatrix [i, j]);
					Console.Write(" ");
				}
				Console.WriteLine("");
			}
		}


		static void makeAdjacencyMatrix(ref int[,] adjacencyMatrix, int numberOfGears, int[,]arrayOfConnections) {

			adjacencyMatrix = new int[numberOfGears, numberOfGears];
			for (int i = 0; i < adjacencyMatrix.GetLength (0); i++) 
			{
				for (int j = 0; j < adjacencyMatrix.GetLength (1); j++) 
				{
					adjacencyMatrix [i, j] = 0;		
				}
			}

			for (int i = 0; i < arrayOfConnections.GetLength (0); i++) 
			{
				adjacencyMatrix [arrayOfConnections[i, 0] - 1, arrayOfConnections[i, 1] - 1] = 1;		
			}
			otputAdjacencyMatrix (adjacencyMatrix);
		}


		static void findOtherWay(int[,] adjacencyMatrix, int problemGear, ref int[]arrayOfDirectionsOfVertices)
		{
			string message;
			message = String.Format("Deleted gear {0}", problemGear + 1);
			Console.WriteLine(message);

			for (int i = 0; i < adjacencyMatrix.GetLength (0); i++) 
			{
				arrayOfDirectionsOfVertices [i] = -1;
			}

			for (int i = 0; i < adjacencyMatrix.GetLength (0); i++) 
			{
				adjacencyMatrix [problemGear, i] = 0;

			}

			bfs (adjacencyMatrix, ref arrayOfDirectionsOfVertices);
		}


		static void bfs(int[,] adjacencyMatrix, ref int[]arrayOfDirectionsOfVertices) 
		{
			Queue<int> queue = new Queue<int>();
			queue.Enqueue (0);
			arrayOfDirectionsOfVertices [0] = 0;
			bool directionChanged = false;
			int numberOfConsideredGears = 0;
			while(queue.Count != 0 && !directionChanged) 
			{
				int currentGear = queue.Dequeue ();
				numberOfConsideredGears++;
				for (int i = 0; i < adjacencyMatrix.GetLength (0); i++) 
				{
					if (adjacencyMatrix [currentGear, i] == 1) 
					{
						queue.Enqueue (i);
						if (arrayOfDirectionsOfVertices [i] == arrayOfDirectionsOfVertices [currentGear]) 
						{
							directionChanged = true;
							string errorMessage;
							errorMessage = String.Format("No, rotation direction changed on the way from {0} to {1}", currentGear + 1, i + 1);
							Console.WriteLine(errorMessage);
							findOtherWay (adjacencyMatrix, currentGear, ref arrayOfDirectionsOfVertices);
							break;
						}
						arrayOfDirectionsOfVertices [i] = arrayOfDirectionsOfVertices [currentGear] == 0 ? 1 : 0;
					}
				}
			}

			if (!directionChanged)
			{
				string successfulMessage;
				successfulMessage = String.Format("Yes, number of considered gears: {0}", numberOfConsideredGears);
				Console.WriteLine(successfulMessage);		
			}
		}
			

		public static void Main (string[] args)
		{
			int numberOfGears = 0;
			int numberOfConnections = 0;
			int[,] arrayOfConnections = new int[0, 2];
			int[,] adjacencyMatrix = new int[0, 0];
			int[] arrayOfDirectionsOfVertices = new int[0];

			InitData (ref numberOfGears, ref numberOfConnections, ref arrayOfConnections, ref arrayOfDirectionsOfVertices);
			makeAdjacencyMatrix (ref adjacencyMatrix, numberOfGears, arrayOfConnections);
			bfs (adjacencyMatrix, ref arrayOfDirectionsOfVertices);
		}
	}
}
