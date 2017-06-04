using System;
using System.Collections.Generic;

namespace Triad
{
	class MainClass
	{
		public static void Main (string[] args)
		{
			Date a = new Date (1, 1, 1970);
			Date b = new Date (2, 1, 1970);
			Time t1 = new Time (1, 1, 24); 
			Time t2 = new Time (1, 1, 59);
			t2.increaseOnOne ();
			Console.WriteLine (t2 - t1);

			var Memories = new Memories();
			Memories.Changed += ChangeListener;
			Memories.Add(t1, a);
			Memories.Add(t2, b);
			Console.WriteLine (Memories);
			Console.WriteLine ("\nFirst tuple: ");
			Console.WriteLine (Memories.GetFirst());
			Console.WriteLine ("\nLast tuple: ");
			Console.WriteLine (Memories.GetLast());
		}

		public static void ChangeListener(ChangeType change)
		{
			switch (change)
			{
				case ChangeType.Add: Console.WriteLine("Element added"); break;
				case ChangeType.Delete: Console.WriteLine("Element deleted"); break;
				case ChangeType.Set: Console.WriteLine("Element setted"); break;
				case ChangeType.Insert: Console.WriteLine("Element inserted"); break;
			}
		}
	}


	/*
     *  interface Triad
        {
            void increaseOnOne();
        }
     * 
     * */


	public abstract class Triad
	{
		public abstract void increaseOnOne();
		public abstract override string ToString();
		public abstract override bool Equals(object obj);
		public abstract override int GetHashCode();
	}


	public class Date : Triad
	{
		public Date(int day, int month, int year)
		{
			this.day = day;
			this.month = month;
			this.year = year;
		}

		public Date() { }

		private int  day
		{
			get;
			set;
		}

		private int month
		{
			get;
			set;
		}

		private int year
		{
			get;
			set;
		}

		public override void increaseOnOne()
		{
			if (day < 31) {
				day++;
			} else if (month < 12) {
				month++;
				day = 1;
			} else {
				year++;
				day = 1;
				month = 1;
			}
		}

		public static Date operator- (Date x, Date y)
		{
			Date result = new Date();
			int xDays = x.day + 30 * x.month + 365 * x.year;
			int yDays = y.day + 30 * y.month + 365 * y.year;
			int diff = Math.Abs (xDays - yDays);
			result.year = (int)(diff / 365);
			result.month = (int)((diff - result.year * 365) / 30);
			result.day = (diff - result.year * 365 - result.month * 30);
			return result;
		}

		public override bool Equals(object x)
		{
			Date obj = (Date)x;
			if (day == obj.day && month == obj.month && year == obj.year) {
				return true;
			} else {
				return false;
			}
		}
			
		public static bool operator== (Date x, Date y)
		{
			return Equals(x, y);
		}

		public static bool operator !=(Date x, Date y)
		{
			return !Equals(x, y);
		}

		public override int GetHashCode()
		{
			return day.GetHashCode() + 31 * month.GetHashCode() + 365 * year.GetHashCode();
		}

		public override string ToString()
		{
			return "Date: (" + day.ToString() + ":" +
				month.ToString() + ":" + year.ToString() + ")";
		}
	}


	public class Time : Triad
	{
		public Time(int hour, int minute, int second)
		{
			this.hour = hour;
			this.minute = minute;
			this.second = second;
		}

		public Time() { }

		private int  hour
		{
			get;
			set;
		}

		private int minute
		{
			get;
			set;
		}

		private int second
		{
			get;
			set;
		}

		public override void increaseOnOne()
		{
			if (second < 59) {
				second++;
			} else if (minute < 59) {
				minute++;
				second = 0;
			} else {
				hour++;
				second = 0;
				minute = 0;
			}
		}

		public static Time operator- (Time x, Time y)
		{
			Time result = new Time();
			int xSeconds = x.second + 60 * x.minute + 60 * 60 * x.hour;
			int ySeconds = y.second + 60 * y.minute + 60 * 60 * y.hour;
			int diff = Math.Abs (xSeconds - ySeconds);
			result.hour = (int)(diff / 365);
			result.minute = (int)((diff - result.hour * 60 * 60) / 60);
			result.second = (diff - result.hour * 60 * 60 - result.minute * 60);
			return result;
		}

		public override bool Equals(object x)
		{
			Time obj = (Time)x;
			if (hour == obj.hour && minute == obj.minute && second == obj.second) {
				return true;
			} else {
				return false;
			}
		}

		public static bool operator== (Time x, Time y)
		{
			return Equals(x, y);
		}

		public static bool operator !=(Time x, Time y)
		{
			return !Equals(x, y);
		}

		public override int GetHashCode()
		{
			return second.GetHashCode() + 60 * minute.GetHashCode() + 60 * 60 * hour.GetHashCode();
		}

		public override string ToString()
		{
			return "Time: (" + hour.ToString() + ":" +
				minute.ToString() + ":" + second.ToString() + ")";
		}
	}


	public enum ChangeType { Add, Insert, Delete, Set }
	public delegate void ChangeHandler(ChangeType change);


	public class Memories
	{
		public List<Tuple<Time, Date>> Elements
		{
			get;
		}

		public event ChangeHandler Changed;

		public Memories()
		{
			Elements = new List<Tuple<Time, Date>>();
		}

		public void Add(Time t, Date d)
		{
			Elements.Add(new Tuple<Time, Date>(t, d));
			if (Changed != null) 
			{
				Changed(ChangeType.Add);
			}
		}

		public Tuple<Time, Date> Get(int index)
		{
			if (index < 0 || index >= Elements.Count) 
			{
				throw new IndexOutOfRangeException();
			}
			return Elements[index];
		}

		public Tuple<Time, Date> GetFirst()
		{
			return Get(0);
		}

		public Tuple<Time, Date> GetLast()
		{
			return Get(Elements.Count - 1);
		}

		public void Set(int index, Time t, Date d)
		{
			if (index < 0 || index >= Elements.Count) 
			{
				throw new IndexOutOfRangeException();
			}
			Elements[index] = new Tuple<Time, Date>(t, d);
			if (Changed != null) 
			{
				Changed(ChangeType.Set);
			}
		}

		public void Insert(int index, Time t, Date d)
		{
			if (index < 0 || index >= Elements.Count) 
			{
				throw new IndexOutOfRangeException();
			}
			Elements.Insert(index, new Tuple<Time, Date>(t, d));
			if (Changed != null) {
				Changed(ChangeType.Insert);
			}
		}

		public void Delete(int index)
		{
			if (index < 0 || index >= Elements.Count) 
			{
				throw new IndexOutOfRangeException();
			}
			Elements.RemoveAt(index);
			if (Changed != null) 
			{
				Changed(ChangeType.Delete);
			}
		}

		public override string ToString()
		{
			return "[" + string.Join("\n ", Elements) + "]";
		}
	}


	public class TriadExeption : Exception
	{
		TriadExeption(String str) : base("TriadExeption: " + str) {}
	}
}
