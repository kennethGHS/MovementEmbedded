//
//  RequestManager.swift
//  SmartCam
//
//  Created by Jasson Rodríguez Méndez on 18/6/21.
//

import Foundation
import SwiftUI
import Combine

class RequestManager : ObservableObject {
    @Published var detectionList = ["No motion detected"]
    
    init () {
        guard let url = URL(string: "http://192.168.100.62:8000/api/images") else { return }
        URLSession.shared.dataTask(with: url) { data, _, _ in
            let detectionList = try! JSONDecoder().decode([String].self, from: data!)
            DispatchQueue.main.async {
                self.detectionList = detectionList
            }
        }.resume()
    }
}
