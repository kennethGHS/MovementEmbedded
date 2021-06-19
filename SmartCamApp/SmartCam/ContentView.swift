//
//  ContentView.swift
//  SmartCam
//
//  Created by Jasson Rodríguez Méndez on 15/6/21.
//

import SwiftUI

struct ContentView: View {
    var body: some View {
        TabView {
        LiveView()
            .tabItem {
                Text("Live")
                Image(systemName: "video.fill")
            }
        DetectionView()
            .tabItem {
                Text("Movement detection")
                Image(systemName: "person.fill")
            }
        }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
